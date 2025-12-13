// Fill out your copyright notice in the Description page of Project Settings.


#include "Range/BulletRangeRecorder.h"

#include "BulletActor.h"

// Sets default values for this component's properties
UBulletRangeRecorder::UBulletRangeRecorder() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UBulletRangeRecorder::BeginPlay() {
	Super::BeginPlay();
	
	AActor* BulletActor = Cast<ABulletActor>(GetOwner());
	if (!BulletActor) {
		return;
	}
	OriginLocation = BulletActor->GetActorLocation();
}


// Called every frame
void UBulletRangeRecorder::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateTraveledDistance();
}

void UBulletRangeRecorder::UpdateTraveledDistance() {
	AActor* BulletActor = Cast<ABulletActor>(GetOwner());
	if (!BulletActor) {
		return;
	}
	FVector Location = BulletActor->GetActorLocation();
	TraveledDistance = FVector::Dist(OriginLocation, Location);
}

