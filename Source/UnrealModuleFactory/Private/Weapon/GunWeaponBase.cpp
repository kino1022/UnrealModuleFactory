// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/GunWeaponBase.h"
#include "Action/ActionAbility.h"
#include "GameplayAbilities/Public/AbilitySystemComponent.h"

AGunWeaponBase::AGunWeaponBase() {
	
}

void AGunWeaponBase::GiveAbilities_Implementation() {
	if (FireActionAbility) {
		GrantedAbilityHandles.Add(GrantAbility(FireActionAbility));
	}
}