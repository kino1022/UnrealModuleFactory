// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/SocketBasedAttackActionAbility.h"
#include "AbilitySystemComponent.h"
#include "Character/CharacterBase.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "AbilitySystemInterface.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

USocketBasedAttackActionAbility::USocketBasedAttackActionAbility()
{
	// デフォルト値の設定
	TraceStartSocketName = FName("hand_r");
	TraceEndSocketName = FName("hand_r");
	StartSocketOffset = FVector::ZeroVector;
	EndSocketOffset = FVector(50.0f, 0.0f, 0.0f); // 手から前方50cm
	TraceRadius = 30.0f;
	TraceChannel = ECC_Pawn;
	bIsAttackWindowActive = false;
	bHasPreviousTrace = false;
}

void USocketBasedAttackActionAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	// 攻撃済みリストをリセット
	HitActors.Empty();
	bIsAttackWindowActive = false;
	bHasPreviousTrace = false;
	PreviousTraceEndLocation = FVector::ZeroVector;
	
	// アニメーションモンタージュを再生
	if (AttackMontage && ActorInfo->AvatarActor.IsValid())
	{
		MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this,
			NAME_None,
			AttackMontage,
			1.0f,
			NAME_None,
			false
		);
		
		if (MontageTask)
		{
			// モンタージュ完了時のコールバック
			MontageTask->OnCompleted.AddDynamic(this, &USocketBasedAttackActionAbility::K2_EndAbility);
			MontageTask->OnInterrupted.AddDynamic(this, &USocketBasedAttackActionAbility::K2_EndAbility);
			MontageTask->OnCancelled.AddDynamic(this, &USocketBasedAttackActionAbility::K2_EndAbility);
			
			MontageTask->ReadyForActivation();
		}
		
		// 重力無効化する場合の処理
		if (bCancelGravity) {
			UCharacterMovementComponent* MovementComp = Cast<ACharacter>(ActorInfo->AvatarActor.Get())->GetCharacterMovement();
			if (MovementComp) {
				cachedGravityScale = MovementComp->GravityScale;
				MovementComp->GravityScale = 0.0f;
			}
		}
	}
	else
	{
		// モンタージュが設定されていない場合は即終了
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}
}

void USocketBasedAttackActionAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	bIsAttackWindowActive = false;
	bHasPreviousTrace = false;
	HitActors.Empty();
	
	if (bCancelGravity) {
		// 重力を元に戻す
		UCharacterMovementComponent* MovementComp = Cast<ACharacter>(ActorInfo->AvatarActor.Get())->GetCharacterMovement();
		if (MovementComp) {
			MovementComp->GravityScale = cachedGravityScale;
		}
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

bool USocketBasedAttackActionAbility::GetSocketLocation(FName SocketName, const FVector& Offset, FVector& OutLocation) const
{
	ACharacterBase* Character = GetOwnerCharacter();
	if (!Character)
	{
		return false;
	}
	
	USkeletalMeshComponent* Mesh = Character->GetMesh();
	if (!Mesh || !Mesh->DoesSocketExist(SocketName))
	{
		UE_LOG(LogTemp, Warning, TEXT("SocketBasedAttackActionAbility: Socket '%s' does not exist!"), *SocketName.ToString());
		return false;
	}
	
	// ソケットのトランスフォームを取得
	FTransform SocketTransform = Mesh->GetSocketTransform(SocketName, RTS_World);
	
	// オフセットを適用（ソケットのローカル空間）
	OutLocation = SocketTransform.TransformPosition(Offset);
	
	return true;
}

void USocketBasedAttackActionAbility::PerformAttackTrace(FGameplayTag AttackTypeTag, bool bDrawDebug)
{
	if (!bIsAttackWindowActive)
	{
		UE_LOG(LogTemp, Warning, TEXT("SocketBasedAttackActionAbility: Attack window is not active."));
		return;
	}
	
	// ソケット位置を取得
	FVector StartLocation, EndLocation;
	
	if (!GetSocketLocation(TraceStartSocketName, StartSocketOffset, StartLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("SocketBasedAttackActionAbility: Failed to get start socket location '%s'"), *TraceStartSocketName.ToString());
		return;
	}
	
	if (!GetSocketLocation(TraceEndSocketName, EndSocketOffset, EndLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("SocketBasedAttackActionAbility: Failed to get end socket location '%s'"), *TraceEndSocketName.ToString());
		return;
	}
	
	// 連続トレース：前フレームの終了位置から現フレームの終了位置までトレース
	// これにより、高速な武器の振りでも判定が抜けにくくなる
	FVector TraceStart = bHasPreviousTrace ? PreviousTraceEndLocation : StartLocation;
	FVector TraceEnd = EndLocation;
	
	// 現在の終了位置を記録
	PreviousTraceEndLocation = EndLocation;
	bHasPreviousTrace = true;
	
	// コリジョン設定
	FCollisionQueryParams QueryParams;
	ACharacterBase* Character = GetOwnerCharacter();
	if (Character)
	{
		QueryParams.AddIgnoredActor(Character);
	}
	QueryParams.bTraceComplex = false;
	
	TArray<FHitResult> HitResults;
	
	// 球体スイープトレース実行
	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		TraceStart,
		TraceEnd,
		FQuat::Identity,
		TraceChannel,
		FCollisionShape::MakeSphere(TraceRadius),
		QueryParams
	);
	
	// デバッグ描画
	if (bDrawDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("bDrawDebug true"));
		
		// トレースラインを描画
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Yellow, false, -1.0f, 0, 2.0f);
		
		// 開始位置と終了位置に球を描画
		DrawDebugSphere(GetWorld(), TraceStart, TraceRadius, 12, FColor::Green, false, -1.0f);
		DrawDebugSphere(GetWorld(), TraceEnd, TraceRadius, 12, FColor::Red, false, -1.0f);
		
		// ソケット位置も表示
		DrawDebugSphere(GetWorld(), StartLocation, 5.0f, 8, FColor::Cyan, false, -1.0f);
	}
	
	// ヒットしたアクターを処理
	if (bHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();
			
			// 既にヒット済みのアクターはスキップ
			if (!HitActor || HitActors.Contains(HitActor))
			{
				continue;
			}
			
			// ヒット済みリストに追加
			HitActors.Add(HitActor);
			
			// ターゲットがAbilitySystemComponentを持っているか確認
			if (IAbilitySystemInterface* TargetASI = Cast<IAbilitySystemInterface>(HitActor))
			{
				UAbilitySystemComponent* TargetASC = TargetASI->GetAbilitySystemComponent();
				
				if (TargetASC && DamageEffectClass)
				{
					// ダメージエフェクトを適用
					FGameplayEffectContextHandle EffectContext = GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
					EffectContext.AddHitResult(Hit);
					
					FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
						DamageEffectClass,
						GetAbilityLevel(),
						EffectContext
					);
					
					if (SpecHandle.IsValid())
					{
						GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
							*SpecHandle.Data.Get(),
							TargetASC
						);
					}
				}
			}
			
			if (bDrawDebug)
			{
				// ヒット位置を表示
				DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 15.0f, 8, FColor::Orange, false, 3.0f);
				DrawDebugLine(GetWorld(), Hit.ImpactPoint, Hit.ImpactPoint + Hit.ImpactNormal * 50.0f, FColor::White, false, 3.0f, 0, 2.0f);
			}
		}
	}
}

