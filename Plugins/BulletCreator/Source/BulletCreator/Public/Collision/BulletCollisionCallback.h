// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BulletCollisionCallback.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class BULLETCREATOR_API UBulletCollisionCallback : public UObject {
	
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintNativeEvent, Category = "HitCallBack|Callback")
	void ExecuteCallback (const struct FBulletHitContext& HitContext);
	virtual void ExecuteCallback_Implementation (const FBulletHitContext& HitContext);
	
};
