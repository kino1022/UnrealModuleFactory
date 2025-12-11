// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Action/FireActionAbility.h"

UFireActionAbility::UFireActionAbility() {
	
}

void UFireActionAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) {
	
}

void UFireActionAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) {
	
}

bool UFireActionAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const {
	return true;
}

void UFireActionAbility::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) {
	
}

void UFireActionAbility::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) {
	
}

void UFireActionAbility::FireLoop() {
	if (!IsActive() || !GetCurrentAbilitySpec()->InputPressed) {
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
		return;
	}
	// 2. コスト再確認: 弾切れ等のチェック（毎発ごとにコストを払う場合）
	if (!CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo)) {
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		return;
	}
	
	UAbilityTask_WaitDelay* FireTask = UAbilityTask_WaitDelay::WaitDelay(
		this,
		0.1f
		);
}

TArray<FString> UFireActionAbility::GetMuzzleSocketNames() const {
	TArray<FString> SocketNames;
	if (MuzzleMesh.IsValid()) {
		const TArray<FName> Names = MuzzleMesh->GetAllSocketNames();
		for (const FName& Name : Names) {
			SocketNames.Add(Name.ToString());
		}
	}
	return SocketNames;
}