// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovementPatternObject.h"
#include "UObject/Object.h"
#include "BulletVelocityPattern.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, EditInlineNew)
class BULLETCREATOR_API UBulletVelocityPattern : public UMovementPatternObject {
	GENERATED_BODY()
public:
	
	UBulletVelocityPattern();
	
	UFUNCTION(BlueprintCallable, Category = "VelocityPattern")
	FVector GetVelocity() const {
		return CurrentVelocity;
	}
	
	UFUNCTION(BlueprintCallable, Category = "VelocityPattern")
	void SetVelocity (const FVector& NewVelocity) {
		CurrentVelocity = NewVelocity;
	}
	
protected:
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "VelocityPattern")
	FVector CurrentVelocity;
};
