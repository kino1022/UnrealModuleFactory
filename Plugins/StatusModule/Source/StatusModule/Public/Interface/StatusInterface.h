// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StatusInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UStatusInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class STATUSMODULE_API IStatusInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Status")
	float GetStatusValue () const;
	virtual float GetStatusValue_Implementation () const =0;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Status")
	void SetStatusValue (const float value);
	virtual void SetStatusValue_Implementation (const float value) =0;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Status")
	void IncreaseStatusValue (const float delta);
	virtual void IncreaseStatusValue_Implementation (const float delta) =0;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Status")
	void DecreaseStatusValue (const float delta);
	virtual void DecreaseStatusValue_Implementation (const float delta) =0;
	
};
