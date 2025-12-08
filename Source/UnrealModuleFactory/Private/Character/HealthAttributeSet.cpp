// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HealthAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UHealthAttributeSet::UHealthAttributeSet() {
	
}

void UHealthAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UHealthAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHealthAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UHealthAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) {
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute()) {
		
	}
	
	if (Attribute == GetMaxHealthAttribute()) {
		
	}
	
}

void UHealthAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) {
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute()) {
		
	}
	
	if (Data.EvaluatedData.Attribute == GetMaxHealthAttribute()) {
		
	}
	
}

void UHealthAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHealthAttributeSet, Health, OldHealth);
}

void UHealthAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHealthAttributeSet, MaxHealth, OldMaxHealth);
}
