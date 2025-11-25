// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "UObject/Object.h"
#include "TransitionTrigger.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BULLETCREATOR_API UTransitionTrigger : public UObject
{
	GENERATED_BODY()
	
public:
	
	UTransitionTrigger() {}
	
	UFUNCTION(BlueprintCallable, Category = "Transition Trigger")
	void Initialize(ABullet* InOwner);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Transition Trigger")
	void PreInitialize(ABullet* InOwner);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Transition Trigger")
	void PostInitialize();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Transition Trigger")
	bool CheckTransition();
	virtual bool CheckTransition_Implementation() { return false;}
	
protected:
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Transition Trigger")
	TObjectPtr<ABullet> OwnerActor;
	
};
