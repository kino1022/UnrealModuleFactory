// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/SprintActionAbility.h"
#include "AbilitySystemComponent.h"
#include "Character/CharacterBase.h"

USprintActionAbility::USprintActionAbility() {
}

void USprintActionAbility::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) {
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	UE_LOG(LogTemp, Warning, TEXT("SprintActionAbility: InputPressed called."));
	ActivateAbility(Handle, ActorInfo, ActivationInfo, nullptr);
}

void USprintActionAbility::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) {
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	UE_LOG(LogTemp, Warning, TEXT("SprintActionAbility: InputReleased called."));
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void USprintActionAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) {
	
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	AbilitySystem = GetOwnerCharacter()->GetAbilitySystemComponent();
	
	if (!AbilitySystem.IsValid()) {
		return;
	}
	
	UAbilitySystemComponent* AbilitySystemComponent = AbilitySystem.Get();
	
	if (AbilitySystemComponent) {
		// スプリント用のGameplayEffectSpecを作成
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent
			->MakeOutgoingSpec(
				SprintEffect,
				0.0f,
				AbilitySystemComponent->MakeEffectContext()
			);
		
		if (SpecHandle.IsValid()) {
			
			// DataTagに対してSetByCallerでSprintRateを設定
			SpecHandle.Data.Get()->SetSetByCallerMagnitude(
				SprintTag,
				SprintRate
				);
			
			// ターゲットに対してGameplayEffectを適用
			ActiveGameplayEffect = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(
				*SpecHandle.Data,
				AbilitySystemComponent
				);
		}
	}
}

void USprintActionAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) {
	
	if (!ActiveGameplayEffect.IsValid() && AbilitySystem.IsValid()) {
		return;
	}
	
	UAbilitySystemComponent* AbilitySystemComponent = AbilitySystem.Get();
	
	if (AbilitySystemComponent) {
		AbilitySystemComponent->RemoveActiveGameplayEffect(ActiveGameplayEffect);
		ActiveGameplayEffect.Invalidate();
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
