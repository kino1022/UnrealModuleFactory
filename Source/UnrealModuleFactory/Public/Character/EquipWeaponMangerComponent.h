// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "EquipWeaponMangerComponent.generated.h"


class AWeaponBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALMODULEFACTORY_API UEquipWeaponMangerComponent : public UActorComponent {
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipWeaponMangerComponent();
	
	virtual void BeginPlay() override;
	
	UFUNCTION(Blueprintable, Category = "Equip Weapon Manager")
	void EquipWeapon (TSubclassOf<AWeaponBase> WeaponClass);
	
	UFUNCTION(BlueprintNativeEvent, Category = "Equip Weapon Manager")
	void OnPreEquipWeapon (TSubclassOf<AWeaponBase> WeaponClass);
	virtual void OnPreEquipWeapon_Implementation (TSubclassOf<AWeaponBase> WeaponClass);
	
	UFUNCTION(BlueprintNativeEvent, Category = "Equip Weapon Manager")
	void OnPostEquipWeapon ();
	virtual void OnPostEquipWeapon_Implementation ();
	
	UFUNCTION(BlueprintCallable, Category = "Equip Weapon Manager")
	FText GetInteractText () const { return InteractText; }

protected:


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Equip Weapon Manager", meta = (GetOptions = "GetEquipSocketNames"))
	FName EquipSocketName;
	
	UFUNCTION()
	TArray<FString> GetEquipSocketNames () const;
	
	UPROPERTY(EditAnywhere, Category = "Equip Weapon Manager")
	UInputAction* InputAction;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Equip Weapon Manager")
	AWeaponBase* EquippedWeapon;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Equip Weapon Manager")
	FText InteractText;
	
	void OnInputStarted(const FInputActionValue& Value);
	
	void OnInputCanceled(const FInputActionValue& Value);
	
	void OnInputTriggered (const FInputActionValue& Value);

public:	
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*
	 * OnInput系の処理の共通部分
	 */
	virtual void OnInputBase(const ETriggerEvent EventType, const FInputActionValue& Value, FText& OutputText) const;
	
};
