// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ActionAbility.generated.h"

/**
 * 
 */
UCLASS()
class UActionAbility : public UGameplayAbility {
	
	GENERATED_BODY()
	
public:
	
	/* オーナーのCharacterBaseを取得します。 */
	UFUNCTION(BlueprintCallable, Category = "Action|Ability")
	class ACharacterBase* GetOwnerCharacter () const;
};
