// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Action/ActionAbility.h"
#include "ActionAbilitySystemComponent.generated.h"

class UAbilityInputConfig;
class UActionAbilitySet;

/**
 * Enhanced InputとGameplayAbilitySystemを統合したカスタムAbilitySystemComponent
 * 
 * 使用方法:
 * 1. ActionAbilitySetを作成し、付与したいアビリティを設定
 * 2. AbilityInputConfigを作成し、InputAction→InputTagのマッピングを設定
 * 3. キャラクターのPossessedByでInitializeAbilities()を呼び出す
 */
UCLASS()
class UNREALMODULEFACTORY_API UActionAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	
	virtual void BeginPlay() override;
	
	/**
	 * デフォルトアビリティセットからアビリティを付与します
	 * PossessedBy（サーバー）またはOnRep_PlayerState（クライアント）で呼び出してください
	 * 重複呼び出しは自動的に防止されます
	 */
	UFUNCTION(BlueprintCallable, Category = "Action|Ability|ASC")
	void InitializeAbilities();
	
	/* アビリティに対して入力が行われた際に呼び出されるメソッド */
	void AbilityInputStarted (const FGameplayTag& InputTag);
	
	/* アビリティに対しての入力が終了した際に呼び出されるメソッド */
	void AbilityInputCanceled (const FGameplayTag& InputTag);
	
	/* アクティブなアビリティを取得する */
	UFUNCTION(BlueprintCallable, Category = "Action|Ability|ASC")
	void GetActiveAbilities(TArray<UGameplayAbility*>& OutActiveAbilities);
	
	/**
	 * 個別にアビリティを付与します
	 * サーバー権限が必要です
	 */
	UFUNCTION(BlueprintCallable, Category = "Action|Ability|ASC")
	void GiveActionAbility(TSubclassOf<UActionAbility> AbilityClass, int32 Level = 1, int32 InputID = -1);

protected:
	
	/* 対応するアビリティのコールバック呼び出しを行うメソッド */
	void ProcessAbilityInput(const FGameplayTag& InputTag, bool Pressed);
	
	/**
	 * キャラクターに付与するデフォルトアビリティセット
	 * DataAssetとして作成し、ここに設定してください
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Action|Ability")
	TObjectPtr<UActionAbilitySet> DefaultAbilitySet;
	
	// アビリティが既に初期化されたかのフラグ（重複防止用）
	bool bAbilitiesInitialized = false;
};
