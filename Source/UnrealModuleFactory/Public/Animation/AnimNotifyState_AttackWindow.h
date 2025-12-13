// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayTagContainer.h"
#include "AnimNotifyState_AttackWindow.generated.h"

struct FGameplayTag ;
/**
 * アニメーションモンタージュ内で攻撃判定を有効化する期間を定義するAnimNotifyState
 * NotifyBeginで攻撃判定開始、NotifyEndで攻撃判定終了を通知します
 */
UCLASS(Blueprintable, BlueprintType, meta = (DisplayName = "Attack Window"))
class UNREALMODULEFACTORY_API UAnimNotifyState_AttackWindow : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	
	UAnimNotifyState_AttackWindow();
	
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
protected:
	
	/** 攻撃判定の種類（軽攻撃、重攻撃など）を識別するためのタグ */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	FGameplayTag AttackTypeTag;
	
	/** 攻撃判定を毎フレーム実行するか（連続ヒット可能） */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	bool bContinuousDetection = false;
	
	/** デバッグ用：攻撃判定の範囲を可視化 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug")
	bool bDrawDebug = false;

#if WITH_EDITOR
	virtual FString GetNotifyName_Implementation() const override;
#endif
};

