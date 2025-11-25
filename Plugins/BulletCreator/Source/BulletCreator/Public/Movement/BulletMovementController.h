// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletDirectionLogic.h"
#include "BulletSpeedLogic.h"
#include "Components/ActorComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BulletMovementController.generated.h"

UCLASS( ClassGroup=(BulletMovement), meta=(BlueprintSpawnableComponent) , Blueprintable, BlueprintType)
class UBulletMovementController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBulletMovementController();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool SetSpeedLogic(UBulletSpeedLogic* NextLogic);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool SetDirectionLogic(UBulletDirectionLogic* NextLogic);

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement Controller")
	TObjectPtr<UBulletSpeedLogic> SpeedLogic;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement Controller")
	TObjectPtr<UBulletDirectionLogic> DirectionLogic;

	//弾丸の移動量
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement Controller")
	FVector Velocity;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement Controller")
	UProjectileMovementComponent* MovementComponent;

	
protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;
	
	///速度を計算する
	UFUNCTION(BlueprintCallable, Category = "Movement Controller")
	virtual FVector CalculateVelocity (const float DeltaTime);
	
	virtual void PreInitialize(){}
	
	virtual void PostInitialize(){}
	
	virtual void OnPreSpeedLogicChange (UBulletSpeedLogic* NextLogic){}
	
	virtual void OnPostSpeedLogicChange (){}
	
	virtual void OnPreDirectionLogicChange (UBulletDirectionLogic* NextLogic){}
	
	virtual void OnPostDirectionLogicChange (){}
	
	virtual void OnPreTick (float DeltaTime) {}
	
	virtual void OnPostTick (float DeltaTime) {}

public:
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
