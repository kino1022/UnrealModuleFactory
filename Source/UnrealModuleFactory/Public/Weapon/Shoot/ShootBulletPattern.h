// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ShootBulletPattern.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class UNREALMODULEFACTORY_API UShootBulletPattern : public UObject {
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintNativeEvent, Category="Shoot|BulletPattern")
	void ExecutePattern (const struct FShootBulletContext& BulletContext);
	virtual void ExecutePattern_Implementation (const FShootBulletContext& BulletContext){}
	
	UFUNCTION(BlueprintCallable, Category="Shoot|BulletPattern")
	class ABulletActor* InstanceBullet (const FShootBulletContext& BulletContext);
	
protected:
	
	/* 生成する弾丸の縦方向へのばらけ具合 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Shoot|BulletPattern", meta = (ClampMin="0.0", ClampMax="180.0"))
	float VerticalSpreadRate = 0.0f;
	
	/* 生成する弾丸の横方向へのばらけ具合 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Shoot|BulletPattern", meta = (ClampMin="0.0", ClampMax="180.0"))
	float HorizontalSpreadRate = 0.0f;
};
