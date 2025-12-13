// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BulletLifetime.generated.h"

/**
 * 
 */
UCLASS()
class BULLETCREATOR_API UBulletLifetime : public UObject {
	
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Bullet|Lifetime")
	bool ShouldDespawn (const class ABulletActor* BulletActor);
	virtual bool ShouldDespawn_Implementation (const ABulletActor* BulletActor) { return false;}
	
};
