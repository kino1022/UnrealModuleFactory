// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/ActionAbilitySystemComponent.h"

void UActionAbilitySystemComponent::AbilityInputStarted (const FGameplayTag& InputTag) {
	if (InputTag.IsValid()) {
		ProcessAbilityInput(InputTag, true);
	}
}

void UActionAbilitySystemComponent::AbilityInputCanceled (const FGameplayTag& InputTag) {
	if (InputTag.IsValid()) {
		ProcessAbilityInput(InputTag, false);
	}
}

void UActionAbilitySystemComponent::ProcessAbilityInput(const FGameplayTag& InputTag, bool Pressed) {
	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities()) {
		if (Spec.Ability && Spec.DynamicAbilityTags.HasTagExact(InputTag)) {
			if (Pressed) {
				// 入力押しイベントをスペックに通知
				Spec.InputPressed = true;
                
				// アビリティがActiveでなければ起動を試みる
				if (Spec.IsActive()) {
					// 既に起動中の場合、Inputイベントだけを送る（WaitInputPressなどに反応させるため）
					AbilitySpecInputPressed(Spec);
				}
				else {
					TryActivateAbility(Spec.Handle);
				}
			}
			else {
				// 入力離しイベントを通知
				Spec.InputPressed = false;
                
				if (Spec.IsActive()) {
					// WaitInputReleaseなどが反応するように通知
					AbilitySpecInputReleased(Spec);
				}
			}
		}
	}
}

void UActionAbilitySystemComponent::GetActiveAbilities(TArray<UGameplayAbility*>& OutActiveAbilities) {
	
	ABILITYLIST_SCOPE_LOCK();
	
	OutActiveAbilities.Empty();
	
	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities()) {
		if (Spec.IsActive()) {
			if (UGameplayAbility* Ability = Spec.GetPrimaryInstance()) {
				OutActiveAbilities.Add(Ability);
			}
		}
	}
}