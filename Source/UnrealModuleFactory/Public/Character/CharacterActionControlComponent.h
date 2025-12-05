// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterActionControlComponent.generated.h"


UCLASS( Blueprintable, BlueprintType,ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALMODULEFACTORY_API UCharacterActionControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterActionControlComponent();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Input")
	void Move(const struct FInputActionValue& Value);
	virtual void Move_Implementation(const FInputActionValue& Value);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent(UInputComponent* PlayerInputComponent);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	class UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	class ACharacterBase* CharacterActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	class UCameraComponent* CameraComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	class UCharacterMovementComponent* MovementComponent;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
