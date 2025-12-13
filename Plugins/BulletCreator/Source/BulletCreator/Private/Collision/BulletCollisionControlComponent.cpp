// Fill out your copyright notice in the Description page of Project Settings.


#include "Collision/BulletCollisionControlComponent.h"
#include "Collision/BulletCollisionCallback.h"
#include "Collision/BulletHitContext.h"

// Sets default values for this component's properties
UBulletCollisionControlComponent::UBulletCollisionControlComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UBulletCollisionControlComponent::BeginPlay() {
	Super::BeginPlay();
}


// Called every frame
void UBulletCollisionControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBulletCollisionControlComponent::OnHit (const FBulletHitContext& HitContext) {
	if (HitCallbacks.Num() == 0) {
		return;
	}
	for (UBulletCollisionCallback* Callback : HitCallbacks) {
		if (!Callback) {
			continue;
		}
		Callback->ExecuteCallback(HitContext);
	}
}

bool UBulletCollisionControlComponent::AddHitCallback (UBulletCollisionCallback* SetCallback) {
	if (!SetCallback) {
		return false;
	}
	HitCallbacks.AddUnique(SetCallback);
	return true;
}

bool UBulletCollisionControlComponent::RemoveHitCallback (UBulletCollisionCallback* RemoveCallback) {
	if (!RemoveCallback) {
		return false;
	}
	return HitCallbacks.Remove(RemoveCallback) > 0;
}

void UBulletCollisionControlComponent::ClearHitCallbacks () {
	HitCallbacks.Empty();
}

