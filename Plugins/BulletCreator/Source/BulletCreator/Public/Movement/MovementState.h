// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletDirectionLogic.h"
#include "BulletSpeedLogic.h"
#include "TransitionTrigger.h"
#include "UObject/Object.h"
#include "MovementState.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BULLETCREATOR_API UMovementState : public UObject
{

	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement State")
	UBulletSpeedLogic* SpeedLogic;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement State")
	UBulletDirectionLogic* DirectionLogic;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement State")
	TMap<UTransitionTrigger*, UMovementState*> TransitionMap;
	
	//ステートの初期化を行う
	UFUNCTION(BlueprintCallable, Category = "Movement State")
	void InitializeState (ABullet* InOwner);
	
};
