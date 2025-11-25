// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterInitData.h"
#include "HealthStatusComponent.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UHealthStatusComponent;

UCLASS()
class UNREALMODULEFACTORY_API ACharacterBase : public ACharacter{
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

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CharacterBase")
	FCharacterInitData InitData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CharacterBase")
	UHealthStatusComponent* Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CharacterBase")
	UMaxHealthComponent* MaxHealth;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
