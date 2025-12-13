// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "AttackHitInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UAttackHitInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * AnimNotifyState_AttackWindowとGameplayAbility間で攻撃判定を連携するためのインターフェース
 * キャラクターやアビリティがこのインターフェースを実装することで、
 * アニメーションのタイミングに合わせた攻撃判定が可能になります
 */
class UNREALMODULEFACTORY_API IAttackHitInterface
{
	GENERATED_BODY()

public:
	
	/**
	 * 攻撃判定ウィンドウが開始されたときに呼ばれる
	 * @param AttackTypeTag 攻撃の種類を示すGameplayTag
	 * @param bDrawDebug デバッグ描画を有効にするか
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat|Attack")
	void OnAttackWindowBegin(FGameplayTag AttackTypeTag, bool bDrawDebug);
	virtual void OnAttackWindowBegin_Implementation(FGameplayTag AttackTypeTag, bool bDrawDebug) {}
	
	/**
	 * 攻撃判定を実行する（毎フレームまたは一度だけ）
	 * @param AttackTypeTag 攻撃の種類を示すGameplayTag
	 * @param bDrawDebug デバッグ描画を有効にするか
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat|Attack")
	void ExecuteAttackHitDetection(FGameplayTag AttackTypeTag, bool bDrawDebug);
	virtual void ExecuteAttackHitDetection_Implementation(FGameplayTag AttackTypeTag, bool bDrawDebug) {}
	
	/**
	 * 攻撃判定ウィンドウが終了したときに呼ばれる
	 * @param AttackTypeTag 攻撃の種類を示すGameplayTag
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat|Attack")
	void OnAttackWindowEnd(FGameplayTag AttackTypeTag);
	virtual void OnAttackWindowEnd_Implementation(FGameplayTag AttackTypeTag) {}
};

