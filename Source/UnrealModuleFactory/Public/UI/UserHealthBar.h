// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Character/HealthAttributeSet.h"
#include "GameplayEffectTypes.h"
#include "UserHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMODULEFACTORY_API UUserHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable, Category="Player HUD")
	virtual bool SetCharacterModel (class ACharacterBase* CharacterModel);
	
	UFUNCTION(BlueprintNativeEvent, Category="Player HUD")
	void UpdateHealthBar();
	virtual void UpdateHealthBar_Implementation();
	
	void OnChangeHealth(const FOnAttributeChangeData& Data);

	void OnChangeMaxHealth(const FOnAttributeChangeData& Data);

public:
	
	/* 体力表示のプログレスバー */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Player HUD", meta = (BindWidget))
	class UProgressBar* HealthBar;
	
	/* 体力表示のテキスト */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Player HUD", meta = (BindWidget))
	class UTextBlock* TextView;
	
	/* 値を保持しているAttribute */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Player HUD")
	TWeakObjectPtr<const UHealthAttributeSet> HealthAttribute;
	
	/* 体力満タン時のバーの色 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Player HUD")
	FColor MaxColor;
	
	/* 体力ゼロ時のバーの色 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Player HUD")
	FColor MinColor;
	
	FDelegateHandle OnChangeMaxHealthDelegateHandle;
	
	FDelegateHandle OnChangeHealthDelegateHandle;
	
};
