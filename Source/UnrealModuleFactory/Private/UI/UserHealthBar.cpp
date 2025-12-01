// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UserHealthBar.h"

#include "Character/CharacterBase.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Interface/HealthProviderInterface.h"
#include "Interface/MaxHealthProviderInterface.h"
#include "StatusModule/Public/HealthStatusComponent.h"
#include "StatusModule/Public/MaxHealthComponent.h"

void UUserHealthBar::NativeConstruct() {
	Super::NativeConstruct();
}

bool UUserHealthBar::SetCharacterModel(ACharacterBase* CharacterModel) {
	
	//体力の参照がある場合は購読処理を解除しておく
	if (HealthComponent.Get()) {
		//購読解除に失敗した場合はfalseを返す
		if (!UnregisterHealthDelegate()) return false;
	}
	
	//同様に最大体力の参照がある場合は購読処理を解除しておく
	if (MaxHealthComponent.Get()) {
		//購読解除に失敗した場合はfalseを返す
		if (!UnregisterMaxHealthDelegate()) return false;
	}
	
	//体力コンポーネントの取得
	auto HealthComp = IHealthProviderInterface::Execute_GetHealthComponent(CharacterModel);
	//取得に失敗した場合はfalseを返す
	if (!HealthComp) return false;
	
	HealthComponent = HealthComp;
	
	//購読に失敗したならfalseを返す
	if (!RegisterHealthDelegate()) return false;
	
	//最大体力コンポーネントの取得
	auto MaxHealthComp = IMaxHealthProviderInterface::Execute_GetMaxHealthComponent(CharacterModel);
	//取得に失敗した場合はfalseを返す
	if (!MaxHealthComp) return false;
	
	MaxHealthComponent = MaxHealthComp;
	
	//購読に失敗したならfalseを返す
	if (!RegisterMaxHealthDelegate()) return false;
	
	//更新処理を実行
	UpdateHealthBar();
	
	return true;
}

void UUserHealthBar::UpdateHealthBar_Implementation() {
	
	//体力と最大体力の参照がないなら処理を返す
	if (!HealthComponent.Get() || !MaxHealthComponent.Get()) return;
	
	float CurrentHealth = IStatusInterface::Execute_GetStatusValue(HealthComponent.Get());
	
	float MaxHealth = IStatusInterface::Execute_GetStatusValue(MaxHealthComponent.Get());
	
	//体力の割合の計算
	float HealthRatio = 0.0f;
	
	//0除算対策
	if (CurrentHealth == 0.0f || MaxHealth == 0.0f) {
		HealthRatio = 0.0f;
	} else {
		HealthRatio = CurrentHealth / MaxHealth;
	}
	
	//表示テキストを更新する
	if (TextView) {
		FString TextStr = FString::Printf(TEXT(" %d / %d"), FMath::CeilToInt(CurrentHealth), FMath::CeilToInt(MaxHealth));
		TextView->SetText(FText::FromString(TextStr));
	}
	
	//体力バーを更新する
	if (HealthBar) {
		HealthBar->SetPercent(HealthRatio);
		FLinearColor BarColor = FLinearColor::LerpUsingHSV(FLinearColor(MinColor), FLinearColor(MaxColor), HealthRatio);
		HealthBar->SetFillColorAndOpacity(BarColor);
	}
}

bool UUserHealthBar::RegisterHealthDelegate() {
	
	if (!HealthComponent.Get()) return false;
	
	HealthComponent->OnStatusChangedEvent.AddDynamic(this, &UUserHealthBar::UpdateHealthBar);
	
	return true;
}

bool UUserHealthBar::RegisterMaxHealthDelegate() {
	
	if (!MaxHealthComponent.Get()) return false;
	
	MaxHealthComponent->OnStatusChangedEvent.AddDynamic(this, &UUserHealthBar::UpdateHealthBar);
	
	return true;
}

bool UUserHealthBar::UnregisterHealthDelegate() {
	if (!HealthComponent.Get()) return false;
	
	HealthComponent->OnStatusChangedEvent.RemoveDynamic(this, &UUserHealthBar::UpdateHealthBar);
	
	return true;
}

bool UUserHealthBar::UnregisterMaxHealthDelegate() {
	if (!MaxHealthComponent.Get()) return false;
	
	MaxHealthComponent->OnStatusChangedEvent.RemoveDynamic(this, &UUserHealthBar::UpdateHealthBar);
	
	return true;
}
