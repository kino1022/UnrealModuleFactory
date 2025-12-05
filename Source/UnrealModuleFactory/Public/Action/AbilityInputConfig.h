// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityInputAction.h"
#include "InputAction.h"
#include "Engine/DataAsset.h"
#include "AbilityInputConfig.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMODULEFACTORY_API UAbilityInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	
	/*
	 * アビリティに対応する入力アクションの配列
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAbilityInputAction> AbilityInputActions;
	
	/*
	 * 指定したタグに対応する入力アクションを取得します。
	 */
	const FAbilityInputAction* FindInputActionByTag (const FGameplayTag& InputTag) const;
};
