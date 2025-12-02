// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthStatusComponent.h"

#include <locale>

#include "GameFramework/Character.h"

// Sets default values for this component's properties
UHealthStatusComponent::UHealthStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UHealthStatusComponent::BeginPlay()
{
	Super::BeginPlay();
	
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter) {
		MaxHealth = OwnerCharacter->FindComponentByClass<UMaxHealthComponent>();
	}
	
	//最大値変化の購読処理
	if (UStatusComponent* castedMaxHealth = Cast<UStatusComponent>(MaxHealth.GetObject())) {
		castedMaxHealth->OnStatusChangedEvent.AddDynamic(this, &UHealthStatusComponent::OnMaxHealthChanged);
	}
}


// Called every frame
void UHealthStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthStatusComponent::SetStatusValue_Implementation(const float Value) {
	float NextValue = Value;
	
	if (IsValid(MaxHealth.GetObject()) == false) {
		Super::SetStatusValue_Implementation(NextValue);
		return;
	}
	
	//パフォーマンスのために最大値をあらかじめ取得
	float MaxValue = IStatusInterface::Execute_GetStatusValue(MaxHealth.GetObject());
	//最大値を超えているなら補正
	if (Value > MaxValue) {
		NextValue = MaxValue;
	}
	
	Super::SetStatusValue_Implementation(NextValue);
	
	//0以下なら死亡時イベントを発火する
	if (CurrentValue < 0.0f) {
		OnDeadEvent.Broadcast(GetOwner());
	}
}

void UHealthStatusComponent::OnMaxHealthChanged() {
	float Value = IStatusInterface::Execute_GetStatusValue(MaxHealth.GetObject());
	if (Value < CurrentValue) {
		IStatusInterface::Execute_SetStatusValue(this, Value);
	}
}
