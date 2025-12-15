// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/ActionAbilitySystemComponent.h"
#include "Action/ActionAbility.h"
#include "Action/ActionAbilitySet.h"

void UActionAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay(); // 必須: 親クラスの初期化を呼び出す
	
	// アビリティの付与はBeginPlayではなく、InitAbilityActorInfoの後に
	// PossessedByまたはOnRep_PlayerStateで行うべき
}

void UActionAbilitySystemComponent::InitializeAbilities()
{
	// サーバー権限チェック
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("InitializeAbilities: No authority, skipping ability initialization"));
		return;
	}

	// 重複初期化防止
	if (bAbilitiesInitialized)
	{
		UE_LOG(LogTemp, Warning, TEXT("InitializeAbilities: Already initialized, skipping"));
		return;
	}

	// DefaultAbilitySetが設定されていない場合は警告
	if (!DefaultAbilitySet)
	{
		UE_LOG(LogTemp, Warning, TEXT("InitializeAbilities: DefaultAbilitySet is not set on %s"), *GetOwner()->GetName());
		return;
	}

	// AbilitySetからアビリティを付与
	UE_LOG(LogTemp, Log, TEXT("InitializeAbilities: Granting %d abilities from AbilitySet"), DefaultAbilitySet->Abilities.Num());
	
	for (const FActionAbilitySetItem& Item : DefaultAbilitySet->Abilities)
	{
		if (Item.AbilityClass)
		{
			GiveActionAbility(Item.AbilityClass, Item.Level);
			UE_LOG(LogTemp, Log, TEXT("  - Granted ability: %s (Level %d, InputTag: %s)"), 
				*Item.AbilityClass->GetName(), 
				Item.Level, 
				*Item.InputTag.ToString());
		}
	}

	bAbilitiesInitialized = true;
	UE_LOG(LogTemp, Log, TEXT("InitializeAbilities: Complete for %s"), *GetOwner()->GetName());
}


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
		UActionAbility* CastedAbility = Cast<UActionAbility>(Spec.Ability);
		
		if (CastedAbility && CastedAbility->StartTag.MatchesTagEsSxact(InputTag)){
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

void UActionAbilitySystemComponent::GiveActionAbility(TSubclassOf<UActionAbility> AbilityClass, int32 Level, int32 InputID)
{
	if (!AbilityClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("GiveActionAbility: AbilityClass is null"));
		return;
	}

	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("GiveActionAbility: No authority, cannot give ability"));
		return;
	}

	FGameplayAbilitySpec Spec = FGameplayAbilitySpec(
		AbilityClass,
		Level,
		InputID,
		this
	);
	
	GiveAbility(Spec);
}
