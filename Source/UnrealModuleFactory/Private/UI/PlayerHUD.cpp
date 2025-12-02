// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUD.h"

#include "UI/UserHealthBar.h"

void UPlayerHUD::NativeConstruct() {
	
	Super::NativeConstruct();
	
}

void UPlayerHUD::ChangeCharacter_Implementation(ACharacterBase* NextCharacter) {
	if (NextCharacter) {
		PlayerActor = NextCharacter;
		if (HealthBarWidget) {
			HealthBarWidget->SetCharacterModel(NextCharacter);
		}
	}
}
