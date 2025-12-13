// Fill out your copyright notice in the Description page of Project Settings.


#include "Lifetime/BulletLifetimeManageComponent.h"
#include "Lifetime/BulletLifetime.h"
#include "BulletActor.h"

// Sets default values for this component's properties
UBulletLifetimeManageComponent::UBulletLifetimeManageComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UBulletLifetimeManageComponent::BeginPlay() {
	Super::BeginPlay();
}


// Called every frame
void UBulletLifetimeManageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (CalculateShouldDespawn()) {
		GetOwner()->Destroy();
	}
}

bool UBulletLifetimeManageComponent::CalculateShouldDespawn () const {
	
	if (LifetimePolicies.Num() <= 0) {
		return false;
	}
	
	for (UBulletLifetime* LifetimePolicy : LifetimePolicies) {
		if (!LifetimePolicy) {
			continue;
		}
		if (LifetimePolicy->ShouldDespawn(GetOwner<ABulletActor>())) {
			return true;
		}
	}
	return false;
}

