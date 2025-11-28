// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Ammo/AmmoManagerComponent.h"

bool UAmmoManagerComponent::Interactable_Implementation(FInteractContext& Context, FText& InteractText) {
	return AmmoAmount > 0.0f;
}
