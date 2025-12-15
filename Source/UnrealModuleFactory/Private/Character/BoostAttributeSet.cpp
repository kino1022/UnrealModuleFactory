// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BoostAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"

UBoostAttributeSet::UBoostAttributeSet() {
	
}

void UBoostAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UBoostAttributeSet, Boost, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBoostAttributeSet, MaxBoost, COND_None, REPNOTIFY_Always);
}

void UBoostAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) {
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetBoostAttribute()) {
		
	}
	
	if (Attribute == GetMaxBoostAttribute()) {
		
	}
}

void UBoostAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) {
	Super::PostGameplayEffectExecute(Data);
}

void UBoostAttributeSet::OnRep_Boost(const FGameplayAttributeData& OldBoost) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBoostAttributeSet, Boost, OldBoost);
}

void UBoostAttributeSet::OnRep_MaxBoost(const FGameplayAttributeData& OldMaxBoost) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBoostAttributeSet, MaxBoost, OldMaxBoost);
}
