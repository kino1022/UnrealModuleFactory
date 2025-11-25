// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement/BulletMovementController.h"
#include "BulletCreator/Public/Bullet.h"

// Sets default values for this component's properties
UBulletMovementController::UBulletMovementController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBulletMovementController::BeginPlay() {
	Super::BeginPlay();
	
	PreInitialize();

	if (SpeedLogic) SpeedLogic-> Initialize(Cast<ABullet>(GetOwner()));
	
	if (DirectionLogic) DirectionLogic->Initialize(Cast<ABullet>(GetOwner()));
	
	SpeedLogic->Enter();
	DirectionLogic->Enter();
	
	PostInitialize();
	// ...
	
}


// Called every frame
void UBulletMovementController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//更新処理の合間合間にフックポイントを作ってもいいかもしれない、少なくともSuperの実行後と速度の適用前、最後の処理に対してはあった方がいい
	
	OnPreTick(DeltaTime);
	
	if (DirectionLogic) DirectionLogic-> Update();
	
	if (SpeedLogic) SpeedLogic->Update();
	
	FVector NextVelocity = CalculateVelocity(DeltaTime);
	if (!NextVelocity.IsZero() && MovementComponent) {
		MovementComponent->Velocity = NextVelocity;
	}
	
	OnPostTick(DeltaTime);
	// ...
}

bool UBulletMovementController::SetSpeedLogic(UBulletSpeedLogic* NextLogic) {
	
	if (NextLogic == nullptr) {
		return false;
	}
	
	OnPreSpeedLogicChange(NextLogic);
	
	if (!SpeedLogic) {
		SpeedLogic->Exit();
	}
	SpeedLogic = NextLogic;
	SpeedLogic->Enter();
	
	OnPostSpeedLogicChange();
	
	return true;
}

bool UBulletMovementController::SetDirectionLogic(UBulletDirectionLogic* NextLogic) {
	if (NextLogic == nullptr) {
		return false;
	}
	OnPreDirectionLogicChange(NextLogic);
	
	if (!DirectionLogic) {
		DirectionLogic->Exit();
	}
	DirectionLogic = NextLogic;
	DirectionLogic->Enter();
	
	OnPostDirectionLogicChange();
	return true;
}

FVector UBulletMovementController::CalculateVelocity(float DeltaTime) {
	
	///どっちもなかったらゼロベクトルを返す
	if (!SpeedLogic && !DirectionLogic) {
		return FVector::ZeroVector;
	}
	
	return DeltaTime * SpeedLogic->GetSpeed() * DirectionLogic->GetDirection();
}


