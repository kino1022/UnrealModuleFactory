// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/ActionAbility.h"
#include "GameplayEffectTypes.h"
#include "SimpleAttackActionAbility.generated.h"

/**
 * 攻撃判定の形状タイプ
 */
UENUM(BlueprintType)
enum class EAttackTraceShape : uint8
{
	Sphere UMETA(DisplayName = "Sphere"),
	Box UMETA(DisplayName = "Box"),
	Capsule UMETA(DisplayName = "Capsule")
};

/**
 * 近接攻撃アビリティ
 * AnimNotifyState_AttackWindowと連携して、アニメーションのタイミングに合わせた攻撃判定を実行します
 */
UCLASS()
class UNREALMODULEFACTORY_API USimpleAttackActionAbility : public UActionAbility {
	GENERATED_BODY()
	
public:
	
	USimpleAttackActionAbility();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	/** 攻撃判定を実行（AnimNotifyから呼ばれる） */
	UFUNCTION(BlueprintCallable, Category = "Ability|Attack")
	void PerformAttackTrace(FGameplayTag AttackTypeTag, bool bDrawDebug);
	
protected:
	
	/** 再生する攻撃モンタージュ */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack|Animation")
	TObjectPtr<class UAnimMontage> AttackMontage;
	
	/** 攻撃判定の形状（Sphere, Box, Capsule） */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack|Detection")
	EAttackTraceShape TraceShape;
	
	/** 攻撃判定の範囲（球体の半径、ボックスの半サイズ） */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack|Detection")
	FVector TraceExtent;
	
	/** 攻撃判定の開始位置オフセット（キャラクターからの相対位置） */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack|Detection")
	FVector TraceStartOffset;
	
	/** 攻撃判定の終了位置オフセット（キャラクターからの相対位置） */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack|Detection")
	FVector TraceEndOffset;
	
	/** ヒットしたアクターに適用するダメージエフェクト */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack|Damage")
	TSubclassOf<class UGameplayEffect> DamageEffectClass;
	
	/** 攻撃対象のコリジョンチャンネル */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack|Detection")
	TEnumAsByte<ECollisionChannel> TraceChannel;
	
	/** 同じアクターへの重複ヒット防止 */
	UPROPERTY(BlueprintReadOnly, Category = "Attack|Detection")
	TArray<AActor*> HitActors;
	
	/** モンタージュ再生タスク */
	UPROPERTY()
	class UAbilityTask_PlayMontageAndWait* MontageTask;

public:
	
	/** 攻撃判定が有効かどうか */
	UPROPERTY(BlueprintReadOnly, Category = "Attack|Detection")
	bool bIsAttackWindowActive;
};
