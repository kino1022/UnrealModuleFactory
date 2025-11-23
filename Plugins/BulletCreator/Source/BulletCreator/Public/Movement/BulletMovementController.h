// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletDirectionLogic.h"
#include "BulletSpeedLogic.h"
#include "Components/ActorComponent.h"
#include "BulletMovementController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UBulletMovementController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBulletMovementController();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool SetSpeedLogic(UBulletSpeedLogic* speedLogic);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool SetDirectionLogic(UBulletDirectionLogic* directionLogic);

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
	UBulletSpeedLogic* SpeedLogic;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
	UBulletDirectionLogic* DirectionLogic;

	//弾丸の移動量
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
	FVector Velocity;

protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
