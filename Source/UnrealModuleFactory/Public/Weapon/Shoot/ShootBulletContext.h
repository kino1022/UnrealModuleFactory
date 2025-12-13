// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShootBulletContext.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FShootBulletContext {
	
	GENERATED_BODY()
	
	UPROPERTY()
	TObjectPtr<UWorld> SpawnWorld;
	
	UPROPERTY()
	FVector ShootLocation;
	
	UPROPERTY()
	FRotator ShootRotation;
	
	UPROPERTY()
	TSubclassOf<class ABulletActor> ShootBullet;
	
};
