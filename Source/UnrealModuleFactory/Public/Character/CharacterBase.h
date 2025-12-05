// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CharacterInitData.h"
#include "HealthStatusComponent.h"
#include "Action/AbilityInputConfig.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Action/ActionAbilitySystemComponent.h"
#include "Interface/HealthProviderInterface.h"
#include "Interface/MaxHealthProviderInterface.h"
#include "CharacterBase.generated.h"

class UHealthStatusComponent;

UCLASS()
class UNREALMODULEFACTORY_API ACharacterBase : public ACharacter, 
	public IHealthProviderInterface, 
	public IMaxHealthProviderInterface,
	public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();
	
	UFUNCTION(BlueprintCallable, Category="CharacterBase")
	TScriptInterface<IStatusInterface> GetHealthStatus () const {
		return TScriptInterface<IStatusInterface>(Health);
	}
	
	UFUNCTION(BlueprintCallable, Category="CharacterBase")
	TScriptInterface<IStatusInterface> GetMaxHealthStatus () const {
		return TScriptInterface<IStatusInterface>(MaxHealth);
	}

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override {
		return Cast<UAbilitySystemComponent>(AbilitySystemComponent);
	}
	
	virtual UHealthStatusComponent* GetHealthComponent_Implementation() const override {
		return Health;
	}
	
	virtual UMaxHealthComponent* GetMaxHealthComponent_Implementation() const override {
		return MaxHealth;
	}

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category="CharacterBase")
	FCharacterInitData InitData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category="CharacterBase")
	UHealthStatusComponent* Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category="CharacterBase")
	UMaxHealthComponent* MaxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category="CharacterBase")
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category="CharacterBase")
	class UCameraComponent* FollowCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category="CharacterBase")
	UActionAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="CharacterBase")
	TObjectPtr<UAbilityInputConfig> AbilityInputConfig;
	
	UPROPERTY(EditDefaultsOnly, Category="CharacterBase|Input")
	class UInputMappingContext* DefaultMapping;
	
	/* 画面上に配置するHUDのクラス */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CharacterBase")
	TSubclassOf<class UUserWidget> HUDWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CharacterBase")
	UUserWidget* PlayerHUD;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void Input_AbilityInputTagPressed(FGameplayTag InputTag);
	
	void Input_AbilityInputTagReleased(FGameplayTag InputTag);
};
