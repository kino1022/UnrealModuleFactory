// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Character/CharacterBase.h"
#include "Components/ProgressBar.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMODULEFACTORY_API UPlayerHUD : public UUserWidget
{
	
	GENERATED_BODY()
public:
	
	/*　widgetの初期化処理　*/
	virtual void NativeConstruct() override;
	
protected:
	
	/*　表示の対象になるプレイヤー　*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Player HUD")
	ACharacterBase* PlayerActor;
	
	/* 体力バーのウィジェット */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Player HUD")
	class UUserHealthBar* HealthBarWidget;
};
