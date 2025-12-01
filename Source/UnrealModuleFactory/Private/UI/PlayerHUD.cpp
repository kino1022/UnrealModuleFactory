// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUD.h"

#include "UI/UserHealthBar.h"

void UPlayerHUD::NativeConstruct() {
	
	Super::NativeConstruct();
	
	PlayerActor = Cast<ACharacterBase>(GetOwningPlayerPawn());
	
	if (HealthBarWidget && PlayerActor) {
		HealthBarWidget->SetCharacterModel(PlayerActor);
	}
	
}
