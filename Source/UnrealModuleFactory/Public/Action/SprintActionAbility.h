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
	
	// スタミナ消費用のGameplayEffect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SprintActionAbility")
	TSubclassOf<UGameplayEffect> StaminaDrainEffect;
	
	// スタミナ消費量（秒単位）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SprintActionAbility")
	float StaminaDrainRate = 10.0f;
	
	// スタミナチェックの頻度（秒単位）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SprintActionAbility")
	float StaminaCheckInterval = 0.1f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SprintActionAbility")
	TWeakObjectPtr<UAbilitySystemComponent> AbilitySystem;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SprintActionAbility")
	FGameplayTag SprintTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SprintActionAbility")
	FGameplayTag DrainEffectTag;
	
	FActiveGameplayEffectHandle ActiveGameplayEffect;
	FActiveGameplayEffectHandle ActiveStaminaDrainEffect;
	
	FTimerHandle StaminaCheckTimerHandle;
	
	// スタミナをチェックする関数
	UFUNCTION()
	void CheckStamina();
};
