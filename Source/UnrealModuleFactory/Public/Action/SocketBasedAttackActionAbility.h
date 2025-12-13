// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/ActionAbility.h"
#include "GameplayEffectTypes.h"
#include "SocketBasedAttackActionAbility.generated.h"

/**
 * ソケットベースの近接攻撃アビリティ
 * 武器や腕のソケット位置を追従し、アニメーションの動きに沿った攻撃判定を実行します
 * AnimNotifyState_AttackWindowと連携して動作します
 */
UCLASS()
class UNREALMODULEFACTORY_API USocketBasedAttackActionAbility : public UActionAbility
{
	GENERATED_BODY()
	
public:
	
	USocketBasedAttackActionAbility();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	/** 攻撃判定を実行（AnimNotifyから呼ばれる） */
	UFUNCTION(BlueprintCallable, Category = "Ability|Attack")
	void PerformAttackTrace(FGameplayTag AttackTypeTag, bool bDrawDebug);
	
protected:
	
	/** 再生する攻撃モンタージュ */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack|Animation")
	TObjectPtr<class UAnimMontage> AttackMontage;
	
	/** トレース開始位置のソケット名（例: "hand_r", "weapon_start"） */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack|Socket")
	FName TraceStartSocketName;
	
	/** トレース終了位置のソケット名（例: "weapon_tip", "hand_l"） */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack|Socket")
	FName TraceEndSocketName;
	
	/** ソケット位置からの追加オフセット（微調整用） */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack|Socket")
	FVector StartSocketOffset;
	
	/** ソケット位置からの追加オフセット（微調整用） */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack|Socket")
	FVector EndSocketOffset;
	
	/** トレースの半径（球体スイープ） */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack|Detection")
	float TraceRadius;
	
	/** 攻撃対象のコリジョンチャンネル */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack|Detection")
	TEnumAsByte<ECollisionChannel> TraceChannel;
	
	/** ヒットしたアクターに適用するダメージエフェクト */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack|Damage")
	TSubclassOf<class UGameplayEffect> DamageEffectClass;
	
	/** 同じアクターへの重複ヒット防止 */
	UPROPERTY(BlueprintReadOnly, Category = "Attack|Detection")
	TArray<AActor*> HitActors;
	
	/** 前フレームのトレース終了位置（連続トレース用） */
	UPROPERTY()
	FVector PreviousTraceEndLocation;
	
	/** 前フレームでトレースを実行したか */
	UPROPERTY()
	bool bHasPreviousTrace;
	
	/** モンタージュ再生タスク */
	UPROPERTY()
	class UAbilityTask_PlayMontageAndWait* MontageTask;
	
	/** ソケットの位置を取得するヘルパー関数 */
	bool GetSocketLocation(FName SocketName, const FVector& Offset, FVector& OutLocation) const;

public:
	
	/** 攻撃判定が有効かどうか */
	UPROPERTY(BlueprintReadOnly, Category = "Attack|Detection")
	bool bIsAttackWindowActive;
};

