// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Shoot/ShootBulletPattern.h"
#include "BulletActor.h"
#include "Weapon/Shoot/ShootBulletContext.h"

class ABulletActor* UShootBulletPattern::InstanceBullet(const FShootBulletContext& BulletContext) {
	TSubclassOf<ABulletActor> BulletActorClass = BulletContext.ShootBullet;
	if (!BulletActorClass) {
		return nullptr;
	}
	UWorld* World = BulletContext.SpawnWorld;
	if (!World) {
		return nullptr;
	}
	
	FRotator SpawnRotation = BulletContext.ShootRotation;
	//ばらけ具合の計算
	float VerticalSpread = FMath::RandRange(-VerticalSpreadRate / 2.0f, VerticalSpreadRate / 2.0f);
	float HorizontalSpread = FMath::RandRange(-HorizontalSpreadRate / 2.0f, HorizontalSpreadRate / 2.0f);
	SpawnRotation.Pitch += VerticalSpread;
	SpawnRotation.Yaw += HorizontalSpread;
	
	ABulletActor* SpawnedBullet = World->SpawnActor<ABulletActor>(
		BulletActorClass,
		BulletContext.ShootLocation,
		SpawnRotation
	);
	
	if (SpawnedBullet) {
		return SpawnedBullet;
	}
	
	return nullptr;
}
