// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Action/FireActionAbility.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"

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
	
	//...生成処理をここに書く
	
	//タスクの生成
	//なんかEndAbilityが呼ばれると自動でキャンセルが走るからライフタイムを考える必要がないみたい
	UAbilityTask_WaitDelay* Task = UAbilityTask_WaitDelay::WaitDelay(
		this, 
		FireInterval
		);
	
	//射撃のループをバインド
	Task->OnFinish.AddDynamic(this, &UFireActionAbility::OnWaitElapsed);
	//タスク開始
	Task->ReadyForActivation();
}

void UFireActionAbility::OnWaitElapsed() {
	//これで円環を作る
	FireLoop();
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