// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "ActionAbilitySet.generated.h"

class UActionAbility;

/**
 * 付与するアビリティの情報を保持する構造体
 */
USTRUCT(BlueprintType)
struct FActionAbilitySetItem
{
	GENERATED_BODY()

	// 付与するアビリティのクラス
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	TSubclassOf<UActionAbility> AbilityClass;

	// アビリティのレベル
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	int32 Level = 1;

	// このアビリティを起動するInputTag（ActionAbility::StartTagと一致させる）
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability", meta = (Categories = "Input"))
	FGameplayTag InputTag;
};

/**
 * キャラクターに付与するアビリティのセットを定義するDataAsset
 * AbilityInputConfigと組み合わせて使用します
 * 
 * 使用方法:
 * 1. このDataAssetを作成し、付与したいアビリティを登録
 * 2. ActionAbilitySystemComponentのDefaultAbilitySetに設定
 * 3. PossessedByまたはOnRep_PlayerStateでInitializeAbilities()を呼び出し
 */
UCLASS(BlueprintType)
class UNREALMODULEFACTORY_API UActionAbilitySet : public UDataAsset
{
	GENERATED_BODY()

public:
	// 付与するアビリティのリスト
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TArray<FActionAbilitySetItem> Abilities;

	// 指定したInputTagに対応するアビリティ情報を取得
	const FActionAbilitySetItem* FindAbilityByInputTag(const FGameplayTag& InputTag) const;
};

