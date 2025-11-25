// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusComponent.h"

// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatusComponent::SetStatusValue_Implementation(const float value) {
	if (CurrentValue != value) {
		CurrentValue = value;
		OnStatusChangedEvent.Broadcast();
	}
}

float UStatusComponent::GetStatusValue_Implementation() const {
	return CurrentValue;
}

void UStatusComponent::IncreaseStatusValue_Implementation(const float delta) {
	Execute_SetStatusValue(this, CurrentValue + delta);
}

void UStatusComponent::DecreaseStatusValue_Implementation(const float delta) {
	Execute_SetStatusValue(this, CurrentValue - delta);
}
