// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/StaminaAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UStaminaAttributeSet::UStaminaAttributeSet() {
	
}

void UStaminaAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UStaminaAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UStaminaAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
}

void UStaminaAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) {
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetStaminaAttribute()) {
		
	}
	
	if (Attribute == GetMaxStaminaAttribute()) {
		
	}
}

void UStaminaAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) {
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetStaminaAttribute()) {
		
	}

	if (Data.EvaluatedData.Attribute == GetMaxStaminaAttribute()) {
		
	}
}

void UStaminaAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStaminaAttributeSet, Stamina, OldStamina);
}

void UStaminaAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStaminaAttributeSet, MaxStamina, OldMaxStamina);	
}

