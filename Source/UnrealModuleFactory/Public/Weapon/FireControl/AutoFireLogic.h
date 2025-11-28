// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireControlLogic.h"
#include "Weapon/FireControl/FireControlLogic.h"
#include "AutoFireLogic.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMODULEFACTORY_API UAutoFireLogic : public UFireControlLogic
{
	GENERATED_BODY()
	
public:
	
	virtual void OnStartFire_Implementation() override;
	
	virtual void OnStopFire_Implementation() override;
	
	virtual void OnTickFire_Implementation(float DeltaTime) override;
	
protected:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Auto Fire Logic")
	float FireInterval = 0.1f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Auto Fire Logic")
	bool OnFire = false;
	
	FTimerHandle TimerHandle;
	
};
