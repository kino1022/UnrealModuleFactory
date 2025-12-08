// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"
#include "Character/CharacterBase.h"

// Sets default values
AWeaponBase::AWeaponBase() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AWeaponBase::Equip(class ACharacterBase* WeaponOwner) {
	
	OwnerCharacter = WeaponOwner;
	ACharacterBase* OwnerCharPtr = OwnerCharacter.Get();
	if (OwnerCharPtr) {
		OwnerAbilitySystemComponent = OwnerCharPtr->GetAbilitySystemComponent();
	}
	
	PreEquip();
	
	if (UAbilitySystemComponent* AbilitySystem = OwnerAbilitySystemComponent.Get()) {
		//アビリティ付与処理の呼び出し
		GiveAbilities();
		//属性付与処理の呼び出し
		GiveAttributes();
	}
	
	PostEquip();
}

void AWeaponBase::UnEquip() {
	
	if (GrantedAbilityHandles.Num() != 0) {
		for (FGameplayAbilitySpecHandle& AbilityHandle : GrantedAbilityHandles) {
			if (UAbilitySystemComponent* AbilitySystem = OwnerAbilitySystemComponent.Get()) {
				AbilitySystem->ClearAbility(AbilityHandle);
			}
		}
		GrantedAbilityHandles.Empty();
	}
	
	OwnerCharacter.Reset();
	OwnerAbilitySystemComponent.Reset();
}

void AWeaponBase::GiveAbilities_Implementation() {
	
}

void AWeaponBase::GiveAttributes_Implementation() {
	
}

void AWeaponBase::PreEquip_Implementation() {
	
}

void AWeaponBase::PostEquip_Implementation() {
	
}

FGameplayAbilitySpecHandle AWeaponBase::GrantAbility(TSubclassOf<class UGameplayAbility> GrantAbilityClass) {
	if (!OwnerAbilitySystemComponent.IsValid()) {
		return FGameplayAbilitySpecHandle();
	}

	if (UAbilitySystemComponent* AbilitySystem = OwnerAbilitySystemComponent.Get()) {
		FGameplayAbilitySpec Spec = FGameplayAbilitySpec(GrantAbilityClass, 1, INDEX_NONE, this);
		FGameplayAbilitySpecHandle SpecHandle = AbilitySystem->GiveAbility(Spec);
		return SpecHandle;
	}
	
	return FGameplayAbilitySpecHandle();
}
