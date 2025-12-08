// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponBase.h"
#include "GunWeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMODULEFACTORY_API AGunWeaponBase : public AWeaponBase {
	
	GENERATED_BODY()
	
public:
	
	AGunWeaponBase();
	
	virtual void GiveAbilities_Implementation() override;
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GunWeaponBase|Ability")
	TSubclassOf<class UActionAbility> FireActionAbility;
	
};
