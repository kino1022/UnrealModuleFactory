// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "Character/HealthAttributeSet.h"
#include "AttributeBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMODULEFACTORY_API UAttributeBarWidget : public UUserWidget {
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;

	virtual void SetCharacterModel (class ACharacterBase* CharacterModel);

	UFUNCTION(BlueprintNativeEvent, Category = "AttributeBar")
	void UpdateBar();
	virtual void UpdateBar_Implementation();

	void OnChangeCurrentAttribute(const FOnAttributeChangeData& Data);

	void OnChangeMaxAttribute(const FOnAttributeChangeData& Data);

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AttributeBar HUD", meta = (BindWidget))
	class UProgressBar* ProgressBarView;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AttributeBar HUD", meta = (BindWidget))
	class UTextBlock* ValueTextView;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AttributeBar HUD")
	TWeakObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AttributeBar HUD")
	FGameplayAttribute CurrentAttribute;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AttributeBar HUD")
	FGameplayAttribute MaxAttribute;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AttributeBar HUD")
	FColor MaxColor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AttributeBar HUD")
	FColor MinColor;

	FDelegateHandle OnChangeMaxAttributeDelegateHandle;

	FDelegateHandle OnChangeCurrentAttributeDelegateHandle;
	
};
