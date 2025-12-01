// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawn/CharacterSpawner.h"
#include "Public/Character/CharacterBase.h"

// Sets default values
ACharacterSpawner::ACharacterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void ACharacterSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterSpawner::SpawnCharacter_Implementation() {
	
	OnBeforeSpawn();
	
	UWorld* World = GetWorld();
	
	if (World == nullptr) {
		return;
	}
	
	FActorSpawnParameters Prams;
	Prams.Owner = this;
	Prams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
	ACharacterBase* SpawnChar = World->SpawnActor<ACharacterBase>(Character, GetActorLocation(), GetActorRotation(), Prams);
	
	if (Character == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("CharacterSpawner: Character class is not set."));
		return;
	}
	
	OnAfterSpawn(SpawnChar);
	
}

void ACharacterSpawner::OnAfterSpawn_Implementation(ACharacterBase* SpawnedCharacter) {
	SpawnedCharacter->SpawnDefaultController();
}

void ACharacterSpawner::OnBeforeSpawn_Implementation() {
	
}

