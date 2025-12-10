// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovementPatternObject.h"
#include "UObject/Object.h"
#include "PatternTransitionTrigger.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, EditInlineNew)
class BULLETCREATOR_API UPatternTransitionTrigger : public UMovementPatternObject {
	
	GENERATED_BODY()
	
public:
	
	UPatternTransitionTrigger();
	
	UFUNCTION(BlueprintCallable, Category = "TransitionTrigger")
	bool IsTriggered() const {
		return bWasTriggered;
	}
	
	UFUNCTION(BlueprintCallable, Category = "TransitionTrigger")
	void SetTrigger(const bool& bTrigger) {
		bWasTriggered = bTrigger;
	}

protected:
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "TransitionTrigger")
	bool bWasTriggered = false;
	
};
