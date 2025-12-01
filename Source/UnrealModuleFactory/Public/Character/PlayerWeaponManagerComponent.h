// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerWeaponManagerComponent.generated.h"


class AWeaponBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALMODULEFACTORY_API UPlayerWeaponManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerWeaponManagerComponent();
	
	/*
	 * 武器を所持するメソッド
	 */
	virtual void OwnWeapon (TSubclassOf<AWeaponBase> WeaponClass) {}

	/*
	 * 武器の所持を解除するメソッド
	 */
	virtual void DeOwnWeapon (TSubclassOf<AWeaponBase> WeaponClass) {}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	/*
	 * 所持している武器のリスト
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Weapon Manager")
	TArray<TSubclassOf<AWeaponBase>> OwnedWeapons;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
