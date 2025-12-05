#pragma once
#include "GameplayTagContainer.h"
#include "AbilityInputAction.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FAbilityInputAction {
	
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	const class UInputAction* InputAction = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag InputTag;
	
};
