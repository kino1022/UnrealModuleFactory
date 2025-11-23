// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletDirectionLogic.generated.h"

class ABullet;
/**
 * 
 */
UCLASS(Blueprintable)
class BULLETCREATOR_API UBulletDirectionLogic : public UObject
{
	GENERATED_BODY()
public:
	UBulletDirectionLogic();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	FVector GetDirection() {
		Direction.Normalize();
		return Direction;
	}

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Initialize(ABullet* BulletActor);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Movement")
	void PreInitialize(ABullet* BulletActor);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Movement")
	void PostInitialize();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Movement")
	void Enter();
	virtual void Enter_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Movement")
	void Update();
	virtual void Update_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Movement")
	void Exit();
	virtual void Exit_Implementation();

protected:
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Movement")
	ABullet* Bullet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Movement")
	FVector Direction;
};
