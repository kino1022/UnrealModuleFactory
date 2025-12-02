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
	virtual void Move_Implementation(const struct FInputActionValue& Value);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Input")
	void Sprint (const struct FInputActionValue& Value);
	virtual void Sprint_Implementation (const struct FInputActionValue& Value);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
	float WalkSpeed;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
	float SprintSpeed;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
	float AccelerationSmooth = 10.0f;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Movement")
	bool IsSprintInput = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	class UInputMappingContext* MappingContext;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	class UInputAction* MoveInput;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input")
	class ACharacterBase* CharacterActor;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Movement")
	class UCameraComponent* CameraComponent;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Movement")
	class UCharacterMovementComponent* MovementComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	UInputAction* SprintInput;
	
	virtual void SetupInputComponent(class UInputComponent* PlayerInputComponent);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
