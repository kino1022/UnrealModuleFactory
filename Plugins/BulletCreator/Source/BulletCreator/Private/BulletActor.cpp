// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Movement/MovementControlComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ABulletActor::ABulletActor() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletMesh = CreateDefaultSubobject<UMeshComponent>(TEXT("BulletMesh"));
	RootComponent = BulletMesh;
	
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

// Called when the game starts or when spawned
void ABulletActor::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void ABulletActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

