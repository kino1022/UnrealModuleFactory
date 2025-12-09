// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement/State/MovementPatternObject.h"
#include "BulletActor.h"

UMovementPatternObject::UMovementPatternObject() {
	
}

void UMovementPatternObject::Initialize(class ABulletActor* OwnerActor) {
	
	if (!OwnerActor) {
		return;
	}
	
	PreInitialize(OwnerActor);
	BulletActor = OwnerActor;
	PostInitialize();
}

void UMovementPatternObject::Tick(float DeltaTime) {
	PreUpdate(DeltaTime);
	Update(DeltaTime);
	PostUpdate(DeltaTime);
}

TStatId UMovementPatternObject::GetStatId() const {
	RETURN_QUICK_DECLARE_CYCLE_STAT(UBulletVelocityPattern, STATGROUP_Tickables);
}

UWorld* UMovementPatternObject::GetTickableGameObjectWorld() const {
	if (!BulletActor.IsValid()) {
		return nullptr;
	}
	ABulletActor* Bullet = BulletActor.Get();
	if (Bullet) {
		return BulletActor->GetWorld();
	}
	return nullptr;
}
