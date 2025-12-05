// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ActionAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMODULEFACTORY_API UActionAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	
	/* アビリティに対して入力が行われた際に呼び出されるメソッド */
	void AbilityInputStarted (const FGameplayTag& InputTag);
	
	/* アビリティに対しての入力が終了した際に呼び出されるメソッド */
	void AbilityInputCanceled (const FGameplayTag& InputTag);
	
	/* アクティブなアビリティを取得する */
	UFUNCTION(BlueprintCallable, Category = "Action|Ability|ASC")
	void GetActiveAbilities(TArray<UGameplayAbility*>& OutActiveAbilities);
	
protected:
	
	/* 対応するアビリティのコールバック呼び出しを行うメソッド */
	void ProcessAbilityInput(const FGameplayTag& InputTag, bool Pressed);
};
