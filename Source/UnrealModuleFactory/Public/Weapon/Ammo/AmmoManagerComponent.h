// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmmoManagerInterface.h"
#include "Weapon/Interface/InteractBehaviourInterface.h"
#include "Weapon/Interface/InteractConditionInterface.h"
#include "Weapon/WeaponModuleComponent.h"
#include "Weapon/Interface/InteractBehaviourInterface.h"
#include "AmmoManagerComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (WeaponModule), meta = (BlueprintSpawnableComponent) )
class UAmmoManagerComponent : public UWeaponModuleComponent, public IInteractConditionInterface, public IAmmoManagerInterface {
	GENERATED_BODY()
	
public:
	
	UAmmoManagerComponent(){}
	
	virtual int GetConditionPriority_Implementation() override { return ConditionPriority; }

	virtual void SetConditionPriority_Implementation(int NewPriority) override { ConditionPriority = NewPriority; }
	
	virtual bool Interactable_Implementation(FInteractContext& Context, FText& InteractText) override;
	
	virtual int GetAmmo_Implementation() const override {return AmmoAmount;}
	
	virtual void SetAmmo_Implementation(int Amount) override {AmmoAmount = Amount;}
	
	virtual int GetMaxAmmo_Implementation() const override {return MaxAmmoAmount;}
	
	virtual void SetMaxAmmo_Implementation(int MaxAmmo) override {MaxAmmoAmount = MaxAmmo;}

protected:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ammo Manager")
	int Cost = 1.0f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ammo Manager")
	int AmmoAmount = 0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ammo Manager")
	int MaxAmmoAmount = 30;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ammo Manager")
	int ConditionPriority = 0;
	
};
