// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/CharacterBase.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay() {
	Super::BeginPlay();
	
	if (MaxHealth != nullptr) {
		IStatusInterface::Execute_SetStatusValue(MaxHealth, InitData.MaxHealth);
	}
	
	if (Health != nullptr) {
		IStatusInterface::Execute_SetStatusValue(Health, InitData.InitialHealth);
	}
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

