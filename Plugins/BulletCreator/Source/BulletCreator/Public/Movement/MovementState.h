// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MovementState.generated.h"

class UTransitionTrigger;
class UBulletSpeedLogic;
class UBulletDirectionLogic;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BULLETCREATOR_API UMovementState : public UPrimaryDataAsset
{

	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement State")
	UBulletSpeedLogic* SpeedLogic;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement State")
	UBulletDirectionLogic* DirectionLogic;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement State")
	TMap<UTransitionTrigger*, UMovementState*> TransitionMap;
	
};
