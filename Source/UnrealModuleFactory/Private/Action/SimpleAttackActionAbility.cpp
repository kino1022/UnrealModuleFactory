// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/SimpleAttackActionAbility.h"
#include "AbilitySystemComponent.h"
#include "Character/CharacterBase.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "AbilitySystemInterface.h"

USimpleAttackActionAbility::USimpleAttackActionAbility()
{
	// デフォルト値の設定
	TraceShape = EAttackTraceShape::Sphere;
	TraceExtent = FVector(50.0f, 50.0f, 50.0f);
	TraceStartOffset = FVector(0.0f, 0.0f, 0.0f);
	TraceEndOffset = FVector(100.0f, 0.0f, 0.0f);
	TraceChannel = ECC_Pawn;
	bIsAttackWindowActive = false;
}

void USimpleAttackActionAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	// 攻撃済みリストをリセット
	HitActors.Empty();
	bIsAttackWindowActive = false;
	
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
			MontageTask->OnCompleted.AddDynamic(this, &USimpleAttackActionAbility::K2_EndAbility);
			MontageTask->OnInterrupted.AddDynamic(this, &USimpleAttackActionAbility::K2_EndAbility);
			MontageTask->OnCancelled.AddDynamic(this, &USimpleAttackActionAbility::K2_EndAbility);
			
			MontageTask->ReadyForActivation();
		}
	}
	else
	{
		// モンタージュが設定されていない場合は即終了
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}
}

void USimpleAttackActionAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	bIsAttackWindowActive = false;
	HitActors.Empty();
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USimpleAttackActionAbility::PerformAttackTrace(FGameplayTag AttackTypeTag, bool bDrawDebug)
{
	if (!bIsAttackWindowActive)
	{
		return;
	}
	
	ACharacterBase* Character = GetOwnerCharacter();
	if (!Character)
	{
		return;
	}
	
	// キャラクターの位置と向きを取得
	FVector CharacterLocation = Character->GetActorLocation();
	FRotator CharacterRotation = Character->GetActorRotation();
	FVector ForwardVector = Character->GetActorForwardVector();
	FVector RightVector = Character->GetActorRightVector();
	
	// トレース開始位置と終了位置を計算
	FVector StartLocation = CharacterLocation + 
		ForwardVector * TraceStartOffset.X + 
		RightVector * TraceStartOffset.Y + 
		FVector::UpVector * TraceStartOffset.Z;
		
	FVector EndLocation = CharacterLocation + 
		ForwardVector * TraceEndOffset.X + 
		RightVector * TraceEndOffset.Y + 
		FVector::UpVector * TraceEndOffset.Z;
	
	// コリジョン設定
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Character);
	QueryParams.bTraceComplex = false;
	
	TArray<FHitResult> HitResults;
	bool bHit = false;
	
	// 形状に応じたトレース実行
	switch (TraceShape)
	{
		case EAttackTraceShape::Sphere:
		{
			bHit = GetWorld()->SweepMultiByChannel(
				HitResults,
				StartLocation,
				EndLocation,
				FQuat::Identity,
				TraceChannel,
				FCollisionShape::MakeSphere(TraceExtent.X),
				QueryParams
			);
			
			if (bDrawDebug)
			{
				DrawDebugSphere(GetWorld(), StartLocation, TraceExtent.X, 12, FColor::Green, false, 2.0f);
				DrawDebugSphere(GetWorld(), EndLocation, TraceExtent.X, 12, FColor::Red, false, 2.0f);
			}
			break;
		}
		case EAttackTraceShape::Box:
		{
			bHit = GetWorld()->SweepMultiByChannel(
				HitResults,
				StartLocation,
				EndLocation,
				CharacterRotation.Quaternion(),
				TraceChannel,
				FCollisionShape::MakeBox(TraceExtent),
				QueryParams
			);
			
			if (bDrawDebug)
			{
				DrawDebugBox(GetWorld(), StartLocation, TraceExtent, CharacterRotation.Quaternion(), FColor::Green, false, 2.0f);
				DrawDebugBox(GetWorld(), EndLocation, TraceExtent, CharacterRotation.Quaternion(), FColor::Red, false, 2.0f);
			}
			break;
		}
		case EAttackTraceShape::Capsule:
		{
			bHit = GetWorld()->SweepMultiByChannel(
				HitResults,
				StartLocation,
				EndLocation,
				CharacterRotation.Quaternion(),
				TraceChannel,
				FCollisionShape::MakeCapsule(TraceExtent.X, TraceExtent.Z),
				QueryParams
			);
			
			if (bDrawDebug)
			{
				DrawDebugCapsule(GetWorld(), StartLocation, TraceExtent.Z, TraceExtent.X, CharacterRotation.Quaternion(), FColor::Green, false, 2.0f);
				DrawDebugCapsule(GetWorld(), EndLocation, TraceExtent.Z, TraceExtent.X, CharacterRotation.Quaternion(), FColor::Red, false, 2.0f);
			}
			break;
		}
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
				DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 10.0f, 8, FColor::Orange, false, 2.0f);
			}
		}
	}
}

