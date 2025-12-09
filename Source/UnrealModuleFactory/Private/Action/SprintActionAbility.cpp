// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/SprintActionAbility.h"
#include "AbilitySystemComponent.h"
#include "Character/CharacterBase.h"
#include "Character/StaminaAttributeSet.h"
#include "TimerManager.h"

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
	
	UE_LOG(LogTemp, Display, TEXT("SprintAction was Activated"))
	
	AbilitySystem = GetOwnerCharacter()->GetAbilitySystemComponent();
		
	if (!AbilitySystem.IsValid()) {
		return;
	}
	
	UAbilitySystemComponent* AbilitySystemComponent = AbilitySystem.Get();
	
	if (AbilitySystemComponent) {
		
		// スタミナをチェック
		const UStaminaAttributeSet* StaminaAttr = AbilitySystemComponent->GetSet<UStaminaAttributeSet>();
		if (!StaminaAttr || StaminaAttr->GetStamina() <= 0.0f) {
			// スタミナがない場合は即座にアビリティを終了
			EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
			return;
		}
		
		if (ActiveGameplayEffect.IsValid()) {
			AbilitySystemComponent->RemoveActiveGameplayEffect(ActiveGameplayEffect);
			ActiveGameplayEffect.Invalidate();
		}
		
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
		
		// スタミナ消費用のGameplayEffectを適用
		if (StaminaDrainEffect) {
			FGameplayEffectSpecHandle StaminaDrainSpecHandle = AbilitySystemComponent
				->MakeOutgoingSpec(
					StaminaDrainEffect,
					1.0f,
					AbilitySystemComponent->MakeEffectContext()
				);
			
			if (StaminaDrainSpecHandle.IsValid()) {
				// スタミナ消費量を設定
				StaminaDrainSpecHandle.Data.Get()->SetSetByCallerMagnitude(
					DrainEffectTag,
					-StaminaDrainRate
				);
				
				ActiveStaminaDrainEffect = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(
					*StaminaDrainSpecHandle.Data,
					AbilitySystemComponent
				);
			}
		}
		
		// スタミナチェックタイマーを開始
		if (ACharacterBase* Character = Cast<ACharacterBase>(ActorInfo->AvatarActor.Get())) {
			if (UWorld* World = Character->GetWorld()) {
				World->GetTimerManager().SetTimer(
					StaminaCheckTimerHandle,
					this,
					&USprintActionAbility::CheckStamina,
					StaminaCheckInterval,
					true
				);
			}
		}
	}
}

void USprintActionAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) {
	
	// タイマーをクリア
	if (StaminaCheckTimerHandle.IsValid()) {
		if (ACharacterBase* Character = Cast<ACharacterBase>(ActorInfo->AvatarActor.Get())) {
			if (UWorld* World = Character->GetWorld()) {
				World->GetTimerManager().ClearTimer(StaminaCheckTimerHandle);
			}
		}
		StaminaCheckTimerHandle.Invalidate();
	}
	
	if (!AbilitySystem.IsValid()) {
		Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
		return;
	}
	
	UAbilitySystemComponent* AbilitySystemComponent = AbilitySystem.Get();
	
	if (AbilitySystemComponent) {
		// スプリントエフェクトを削除
		if (ActiveGameplayEffect.IsValid()) {
			AbilitySystemComponent->RemoveActiveGameplayEffect(ActiveGameplayEffect);
			ActiveGameplayEffect.Invalidate();
		}
		
		// スタミナ消費エフェクトを削除
		if (ActiveStaminaDrainEffect.IsValid()) {
			AbilitySystemComponent->RemoveActiveGameplayEffect(ActiveStaminaDrainEffect);
			ActiveStaminaDrainEffect.Invalidate();
		}
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USprintActionAbility::CheckStamina() {
	if (!AbilitySystem.IsValid()) {
		return;
	}
	
	UAbilitySystemComponent* AbilitySystemComponent = AbilitySystem.Get();
	if (!AbilitySystemComponent) {
		return;
	}
	
	const UStaminaAttributeSet* StaminaAttr = AbilitySystemComponent->GetSet<UStaminaAttributeSet>();
	if (!StaminaAttr) {
		return;
	}
	
	// スタミナが0以下の場合はアビリティを終了
	if (StaminaAttr->GetStamina() <= 0.0f) {
		UE_LOG(LogTemp, Warning, TEXT("SprintActionAbility: Stamina depleted, ending ability."));
		
		// アビリティをキャンセル
		if (IsActive()) {
			CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
		}
	}
}

