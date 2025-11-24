// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement/BulletMovementController.h"

// Sets default values for this component's properties
UBulletMovementController::UBulletMovementController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBulletMovementController::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBulletMovementController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UBulletMovementController::SetSpeedLogic(UBulletSpeedLogic* NextLogic) {
	return true;
}

bool UBulletMovementController::SetDirectionLogic(UBulletDirectionLogic* NewDirection) {
	return true;
}

