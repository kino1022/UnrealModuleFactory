// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement/MovementControlComponent.h"

#include "BulletActor.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values for this component's properties
UMovementControlComponent::UMovementControlComponent(){

	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UMovementControlComponent::BeginPlay() {
	Super::BeginPlay();
	ABulletActor* BulletActor = Cast<ABulletActor>(GetOwner());
	if (BulletActor) {
		ProjectileMovement = BulletActor->GetProjectileMovement();
	}
}


// Called every frame
void UMovementControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	PreCalculateMovement();
	
	BulletMovement = CalculateMovement();
	
	PostCalculateMovement();
	
	if (!ProjectileMovement.IsValid()) {
		return;
	}
	
	UProjectileMovementComponent* Projectile = ProjectileMovement.Get();
	if (Projectile) {
		PreApplyMovement();
		Projectile->Velocity = BulletMovement;
		PostApplyMovement();
	}
	
}

void UMovementControlComponent::SetBulletSpeed (const float& Speed) {
	CurrentSpeed = Speed;
}

void UMovementControlComponent::SetBulletVelocity (const FVector& Velocity) {
	CurrentVelocity = Velocity;
}

FVector UMovementControlComponent::CalculateMovement () {
	return CurrentVelocity * CurrentSpeed;
}