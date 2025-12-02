// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterActionControlComponent.h"
#include "Character/CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"

// Sets default values for this component's properties
UCharacterActionControlComponent::UCharacterActionControlComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterActionControlComponent::BeginPlay()
{
	Super::BeginPlay();
	
	CharacterActor = Cast<ACharacterBase>(GetOwner());
	if (CharacterActor) {
		
		CameraComponent = CharacterActor->FindComponentByClass<UCameraComponent>();
	}
}


// Called every frame
void UCharacterActionControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCharacterActionControlComponent::Move_Implementation(const struct FInputActionValue& Value) {
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	float PreviousMovementSpeed = MovementComponent->GetMaxSpeed();
	
	float MovementSpeed = IsSprintInput ? SprintSpeed : MovementVector.Size() * WalkSpeed;
	
	if (CharacterActor&& CameraComponent && MovementComponent) {
		
		MovementComponent->MaxWalkSpeed = FMath::FInterpTo(PreviousMovementSpeed, MovementSpeed, GetWorld()->GetDeltaSeconds(), AccelerationSmooth);
		
		const FRotator Rotation = CameraComponent->GetComponentRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		CharacterActor->AddMovementInput(ForwardDirection, MovementVector.Y);
		CharacterActor->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void UCharacterActionControlComponent::Sprint_Implementation(const struct FInputActionValue& Value) {
	if (Value.IsNonZero()) {
		IsSprintInput = true;
	}
	else {
		IsSprintInput = false;
	}
}

void UCharacterActionControlComponent::SetupInputComponent(class UInputComponent* PlayerInputComponent) {
	if (UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInput->BindAction(MoveInput, ETriggerEvent::Triggered, this, &UCharacterActionControlComponent::Move);
		EnhancedInput->BindAction(SprintInput, ETriggerEvent::Triggered, this, &UCharacterActionControlComponent::Sprint);
	}
}
