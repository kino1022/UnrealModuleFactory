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
UCLASS(Blueprintable, BlueprintType)
class UNREALMODULEFACTORY_API UPlayerHUD : public UUserWidget
{
	
	GENERATED_BODY()
public:
	
	/*　widgetの初期化処理　*/
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerHUD")
	void ChangeCharacter (ACharacterBase* NextCharacter);
	virtual void ChangeCharacter_Implementation(ACharacterBase* NextCharacter);
	
protected:
	
	/*　表示の対象になるプレイヤー　*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Player HUD")
	ACharacterBase* PlayerActor;
	
	/* 体力バーのウィジェット */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Player HUD")
	class UUserHealthBar* HealthBarWidget;
};
