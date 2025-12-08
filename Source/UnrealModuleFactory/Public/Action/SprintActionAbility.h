// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/ActionAbility.h"
#include "SprintActionAbility.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMODULEFACTORY_API USprintActionAbility : public UActionAbility
{
	GENERATED_BODY()
public :
	
	USprintActionAbility();
	
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SprintActionAbility")
	float SprintRate = 1.5f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SprintActionAbility")
	TSubclassOf<UGameplayEffect> SprintEffect;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SprintActionAbility")
	TWeakObjectPtr<UAbilitySystemComponent> AbilitySystem;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SprintActionAbility")
	FGameplayTag SprintTag;
	
	FActiveGameplayEffectHandle ActiveGameplayEffect;
};
