// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractConditionInterface.generated.h"
struct FInteractContext;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractConditionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREALMODULEFACTORY_API IInteractConditionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact Condition")
	bool Interactable (FInteractContext& Context, FText& InteractText) ;
	virtual bool Interactable_Implementation (FInteractContext& Context, FText& InteractText) =0;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact Condition")
	int GetConditionPriority ();
	virtual int GetConditionPriority_Implementation () =0;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact Condition")
	void SetConditionPriority (int NewPriority);
	virtual void SetConditionPriority_Implementation (int NewPriority) =0;
};
