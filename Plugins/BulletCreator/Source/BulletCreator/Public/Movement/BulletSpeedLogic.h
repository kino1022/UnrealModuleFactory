// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BulletSpeedLogic.generated.h"

class ABullet;
/**
 * 
 */
UCLASS(Blueprintable)
class BULLETCREATOR_API UBulletSpeedLogic : public UObject
{
	GENERATED_BODY()
	
public:

	UBulletSpeedLogic() {Speed = 0.0f;}

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetSpeed () {return Speed;}

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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
	float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Movement")
	ABullet* Bullet; 
};
