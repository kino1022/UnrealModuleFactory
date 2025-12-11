// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Movement/MovementControlComponent.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Collision/BulletCollisionControlComponent.h"

// Sets default values
ABulletActor::ABulletActor() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletSphere = CreateDefaultSubobject<USphereComponent>(FName("SphereComponent"));
	RootComponent = BulletSphere;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	AddOwnedComponent(BulletMesh);

	BulletCollision = CreateDefaultSubobject<UBulletCollisionControlComponent>(TEXT("BulletCollision"));
	AddOwnedComponent(BulletCollision);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	AddOwnedComponent(ProjectileMovement);
	
	MovementControl = CreateDefaultSubobject<UMovementControlComponent>(TEXT("MovementControl"));
	AddOwnedComponent(MovementControl);

}

void ABulletActor::SetOwnerCharacter(class ACharacter* NewOwnerCharacter) {
	if (!NewOwnerCharacter) {
		return;
	}
	OwnerCharacter = NewOwnerCharacter;
}

ACharacter* ABulletActor::GetOwnerCharacter() const {
	if (!OwnerCharacter.IsValid()) {
		return nullptr;
	}
	return OwnerCharacter.Get();
}

UMeshComponent* ABulletActor::GetBulletMesh () const {
	return BulletMesh;
}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay() {
	Super::BeginPlay();
	if (BulletMesh) {
	}
}

// Called every frame
void ABulletActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

