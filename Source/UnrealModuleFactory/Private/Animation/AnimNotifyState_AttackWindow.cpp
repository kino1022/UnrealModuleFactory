// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyState_AttackWindow.h"
#include "Public/Animation/AttackHitInterface.h"

UAnimNotifyState_AttackWindow::UAnimNotifyState_AttackWindow()
{
	bContinuousDetection = false;
	bDrawDebug = false;
}

void UAnimNotifyState_AttackWindow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	if (!MeshComp || !MeshComp->GetOwner())
	{
		return;
	}
	
	// オーナーがIAttackHitInterfaceを実装しているか確認
	if (IAttackHitInterface* AttackInterface = Cast<IAttackHitInterface>(MeshComp->GetOwner()))
	{
		// 攻撃判定開始を通知
		AttackInterface->OnAttackWindowBegin(AttackTypeTag, bDrawDebug);
		
		// 連続判定が不要な場合は、開始時に一度だけ判定実行
		if (!bContinuousDetection)
		{
			AttackInterface->ExecuteAttackHitDetection(AttackTypeTag, bDrawDebug);
		}
	}
}

void UAnimNotifyState_AttackWindow::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	
	if (!bContinuousDetection || !MeshComp || !MeshComp->GetOwner())
	{
		return;
	}
	
	// 連続判定が有効な場合は毎フレーム実行
	if (IAttackHitInterface* AttackInterface = Cast<IAttackHitInterface>(MeshComp->GetOwner()))
	{
		AttackInterface->ExecuteAttackHitDetection(AttackTypeTag, bDrawDebug);
	}
}

void UAnimNotifyState_AttackWindow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	
	if (!MeshComp || !MeshComp->GetOwner())
	{
		return;
	}
	
	// 攻撃判定終了を通知
	if (IAttackHitInterface* AttackInterface = Cast<IAttackHitInterface>(MeshComp->GetOwner()))
	{
		AttackInterface->OnAttackWindowEnd(AttackTypeTag);
	}
}

#if WITH_EDITOR
FString UAnimNotifyState_AttackWindow::GetNotifyName_Implementation() const
{
	if (AttackTypeTag.IsValid())
	{
		return FString::Printf(TEXT("Attack Window: %s"), *AttackTypeTag.ToString());
	}
	return TEXT("Attack Window");
}
#endif

