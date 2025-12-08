// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UNREALMODULEFACTORY_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();
		
	UFUNCTION(BlueprintCallable, Category = "Weapon|Equip")
	virtual void Equip (class ACharacterBase* WeaponOwner);
	
	UFUNCTION(BlueprintCallable, Category = "Weapon|Equip")
	virtual void UnEquip ();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Ability")
	void GiveAbilities ();
	virtual void GiveAbilities_Implementation ();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Ability")
	void GiveAttributes();
	virtual void GiveAttributes_Implementation ();
	
	/*アビリティと属性付与前に呼ばれる仮想メソッド*/
	UFUNCTION(BlueprintNativeEvent, Category = "Weapon|Equip")
	void PreEquip();
	virtual void PreEquip_Implementation();
	
	/*アビリティと属性付与後に呼ばれる仮想メソッド*/
	UFUNCTION(BlueprintNativeEvent, Category = "Weapon|Equip")
	void PostEquip();
	virtual void PostEquip_Implementation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapon|Owner")
	TWeakObjectPtr<ACharacterBase> OwnerCharacter;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapon|Owner")
	TWeakObjectPtr<class UAbilitySystemComponent> OwnerAbilitySystemComponent;
	
	/* 付与したアビリティのスペックを管理する配列 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Ability")
	TArray<struct FGameplayAbilitySpecHandle> GrantedAbilityHandles;
	
	UFUNCTION(BlueprintCallable, Category = "Weapon|Ability")
	struct FGameplayAbilitySpecHandle GrantAbility (TSubclassOf<class UGameplayAbility> GrantAbilityClass);
	
public:	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
