// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collision/BulletCollisionCallback.h"
#include "GameplayTags.h"
#include "OnHitGiveEffectCallback.generated.h"

/**
 * 
 */
UCLASS()
class BULLETCREATOR_API UOnHitGiveEffectCallback : public UBulletCollisionCallback {
	GENERATED_BODY()
public:
	
	virtual void ExecuteCallback_Implementation (const struct FBulletHitContext& HitContext) override;
	
protected:
	
	UPROPERTY(EditAnywhere, Category = "Bullet|Hit|Effect")
	TSubclassOf<class UGameplayEffect> EffectClass;
	
	UPROPERTY(EditAnywhere, Category = "Bullet|Hit|Effect")
	FGameplayTag EffectCallerTag;
	
	UPROPERTY(EditAnywhere, Category = "Bullet|Hit|Effect")
	float CallerValue;
};
