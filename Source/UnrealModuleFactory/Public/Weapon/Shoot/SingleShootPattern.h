// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Shoot/ShootBulletPattern.h"
#include "SingleShootPattern.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMODULEFACTORY_API USingleShootPattern : public UShootBulletPattern {
	GENERATED_BODY()
public:
	virtual void ExecutePattern_Implementation (const FShootBulletContext& BulletContext) override;
};
