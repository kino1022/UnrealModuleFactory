// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BulletSpeedLogic.generated.h"

class ABullet;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BULLETCREATOR_API UBulletSpeedLogic : public UObject
{
	GENERATED_BODY()
	
public:

	UBulletSpeedLogic() {Speed = 0.0f;}

	UFUNCTION(BlueprintCallable, Category = "Speed Logic")
	float GetSpeed () {return Speed;}

	UFUNCTION(BlueprintCallable, Category = "Speed Logic")
	void Initialize(ABullet* BulletActor);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Speed Logic")
	void PreInitialize(ABullet* BulletActor);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Speed Logic")
	void PostInitialize();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Speed Logic")
	void Enter();
	virtual void Enter_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Speed Logic")
	void Update();
	virtual void Update_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Speed Logic")
	void Exit();
	virtual void Exit_Implementation();

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Speed Logic")
	float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Speed Logic")
	ABullet* Bullet; 
};
