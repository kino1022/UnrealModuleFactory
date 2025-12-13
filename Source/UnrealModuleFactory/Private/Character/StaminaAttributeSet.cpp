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
		//スタミナの値が最大値を超えないように制限
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxStamina());
	}
	
	if (Attribute == GetMaxStaminaAttribute()) {
		
	}
}

void UStaminaAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) {
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetStaminaAttribute()) {
		
		float magnitude = Data.EvaluatedData.Magnitude;
		//スタミナ減少時の処理
		if (magnitude < 0.0f) {
			OnDecreaseStamina(Data);
		}
		//スタミナ回復時の処理
		if (magnitude > 0.0f) {
			OnRecoveryStamina(Data);
		}
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

void UStaminaAttributeSet::OnRecoveryStamina(const FGameplayEffectModCallbackData& Data) {
	
}

void UStaminaAttributeSet::OnDecreaseStamina(const FGameplayEffectModCallbackData& Data) {
	AActor* TargetActor = Data.Target.GetAvatarActor_Direct();
	if (!TargetActor) {
		return;
	}
	
	UAbilitySystemComponent* AbilitySystem = GetOwningAbilitySystemComponent();
	if (!AbilitySystem) {
		return;
	}
	
	//スタミナ減少時に回復クールタイムを付与
	if (RecoveryCoolTimeEffectClass) {
		FGameplayEffectContextHandle EffectContext = AbilitySystem->MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle = AbilitySystem->MakeOutgoingSpec(RecoveryCoolTimeEffectClass, 1.0f, EffectContext);
		if (SpecHandle.IsValid()) {
			AbilitySystem->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

