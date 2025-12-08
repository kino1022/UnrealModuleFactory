// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UserHealthBar.h"

#include "Character/CharacterBase.h"
#include "Character/HealthAttributeSet.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UUserHealthBar::NativeConstruct() {
	Super::NativeConstruct();
}

bool UUserHealthBar::SetCharacterModel(ACharacterBase* CharacterModel) {
	
	//既に購読がある場合は購読解除処理
	if (OnChangeMaxHealthDelegateHandle.IsValid()) {
		OnChangeHealthDelegateHandle.Reset();
	}
	
	//体力変化処理の購読でも同様にして解除処理を行う
	if (OnChangeHealthDelegateHandle.IsValid()) {
		OnChangeMaxHealthDelegateHandle.Reset();
	}
	
	UAbilitySystemComponent* AbilitySystem = CharacterModel->GetAbilitySystemComponent();
	
	//体力Attributeの変化を購読する処理
	if (AbilitySystem) {
		
		OnChangeHealthDelegateHandle = AbilitySystem
			->GetGameplayAttributeValueChangeDelegate(UHealthAttributeSet::GetHealthAttribute())
			.AddUObject(this, &UUserHealthBar::OnChangeHealth);
		
		OnChangeMaxHealthDelegateHandle = AbilitySystem
			->GetGameplayAttributeValueChangeDelegate(UHealthAttributeSet::GetMaxHealthAttribute())
			.AddUObject(this, &UUserHealthBar::OnChangeMaxHealth);
		
	}
	else {
		return false;
	}
	
	HealthAttribute = AbilitySystem->GetSet<UHealthAttributeSet>();
	
	//登録処理が終了したので更新
	UpdateHealthBar();
	
	return true;
}

void UUserHealthBar::UpdateHealthBar_Implementation() {
	
	//体力Attributeが設定されていない場合は処理を抜ける
	if (HealthAttribute == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Health attribute is null"));
		return;
	}
	
	//体力Attributeが有効でない場合は処理を抜ける
	if (!HealthAttribute.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT("Health attribute is not valid"));
		return;
	}
	
	const UHealthAttributeSet* Attribute = HealthAttribute.Get();
	
	//現在の体力を取得
	float CurrentValue = Attribute->GetHealth();
	//最大体力を取得
	float MaxValue = Attribute->GetMaxHealth();
	
	//最大値を超過していた場合は最大値で上書きして補正
	if (CurrentValue > MaxValue) {
		CurrentValue = MaxValue;
	}
	
	//体力の割合を取得
	float HealthRatio = MaxValue < 0.0f || CurrentValue < 0.0f ? 0.0f : CurrentValue / MaxValue;
	
	//表示テキストを更新する
	if (TextView) {
		FString TextStr = FString::Printf(TEXT(" %d / %d"), FMath::CeilToInt(CurrentValue), FMath::CeilToInt(MaxValue));
		TextView->SetText(FText::FromString(TextStr));
	}
	
	//体力バーを更新する
	if (HealthBar) {
		HealthBar->SetPercent(HealthRatio);
		FLinearColor BarColor = FLinearColor::LerpUsingHSV(FLinearColor(MinColor), FLinearColor(MaxColor), HealthRatio);
		HealthBar->SetFillColorAndOpacity(BarColor);
	}
	
}

void UUserHealthBar::OnChangeHealth(const FOnAttributeChangeData& Data) {
	UpdateHealthBar();
}

void UUserHealthBar::OnChangeMaxHealth(const FOnAttributeChangeData& Data) {
	UpdateHealthBar();
}
