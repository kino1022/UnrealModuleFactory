// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AttributeBarWidget.h"

#include "Character/CharacterBase.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UAttributeBarWidget::NativeConstruct() {
	Super::NativeConstruct();
}

void UAttributeBarWidget::SetCharacterModel(class ACharacterBase* CharacterModel) {

	if (!CharacterModel) {
		return;
	}
	
	if (OnChangeCurrentAttributeDelegateHandle.IsValid()) {
		OnChangeCurrentAttributeDelegateHandle.Reset();
	}

	if (OnChangeMaxAttributeDelegateHandle.IsValid()) {
		OnChangeMaxAttributeDelegateHandle.Reset();
	}

	UAbilitySystemComponent* AbilitySystem = CharacterModel->GetAbilitySystemComponent();

	if (AbilitySystem) {

		OnChangeCurrentAttributeDelegateHandle =
			AbilitySystem ->
				GetGameplayAttributeValueChangeDelegate(CurrentAttribute)
				.AddUObject(this, &UAttributeBarWidget::OnChangeCurrentAttribute);

		OnChangeMaxAttributeDelegateHandle =
			AbilitySystem ->
				GetGameplayAttributeValueChangeDelegate(MaxAttribute)
				.AddUObject(this, &UAttributeBarWidget::OnChangeMaxAttribute);
	}

	AbilitySystemComponent = AbilitySystem;

	UpdateBar();
}

void UAttributeBarWidget::UpdateBar_Implementation() {

	if (!AbilitySystemComponent.IsValid()) {
		return;
	}

	UAbilitySystemComponent* AbilitySystem = AbilitySystemComponent.Get();

	if (AbilitySystem) {
		float CurrentValue = AbilitySystem->GetNumericAttribute(CurrentAttribute);
		float MaxValue = AbilitySystem->GetNumericAttribute(MaxAttribute);

		if (CurrentValue < MaxValue) {
			CurrentValue = MaxValue;
		}

		float ValueRatio = CurrentValue / MaxValue;

		if (ValueTextView) {
			FString TextStr = FString::Printf(TEXT("%d / %d"), FMath::CeilToInt(CurrentValue), FMath::CeilToInt(MaxValue));
			ValueTextView->SetText(FText::FromString(TextStr));
		}

		if (ProgressBarView) {
			ProgressBarView->SetPercent(ValueRatio);
			FLinearColor BarColor = FLinearColor::LerpUsingHSV(FLinearColor(MinColor), FLinearColor(MaxColor), ValueRatio);
			ProgressBarView->SetFillColorAndOpacity(BarColor);
		}
	}
}

void UAttributeBarWidget::OnChangeCurrentAttribute(const FOnAttributeChangeData& Data) {
	UpdateBar();
}

void UAttributeBarWidget::OnChangeMaxAttribute(const FOnAttributeChangeData& Data) {
	UpdateBar();
}


