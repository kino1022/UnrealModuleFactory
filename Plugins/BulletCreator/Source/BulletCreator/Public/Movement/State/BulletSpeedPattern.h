// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovementPatternObject.h"
#include "UObject/Object.h"
#include "BulletSpeedPattern.generated.h"

/**
 * 
 */
UCLASS()
class BULLETCREATOR_API UBulletSpeedPattern : public UMovementPatternObject {
	GENERATED_BODY()
	
public:
	
	UBulletSpeedPattern();
	
	UFUNCTION(BlueprintCallable, Category = "BulletSpeed")
	float GetSpeed() const {
		return CurrentSpeed;
	}
	
	UFUNCTION(BlueprintCallable, Category = "BulletSpeed")
	void SetSpeed (const float& NewSpeed) {
		CurrentSpeed = NewSpeed;
	}
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BulletSpeed")
	float CurrentSpeed;
	
};
