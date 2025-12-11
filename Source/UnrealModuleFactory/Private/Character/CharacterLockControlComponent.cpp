// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterLockControlComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UCharacterLockControlComponent::UCharacterLockControlComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterLockControlComponent::BeginPlay() {
	Super::BeginPlay();
	
	UInputComponent* InputComponent = GetOwner()->InputComponent;
	if (InputComponent) {
		SetupInput(InputComponent);
	}
	
	UCameraComponent* FollowCam = Cast<ACharacter>(GetOwner())->GetComponents<UCameraComponent>();
	
	if (FollowCam) {
		FollowCamera = FollowCam;
	}
	
}

void UCharacterLockControlComponent::SetupInput(UInputComponent* InputComponent) {
	if (!InputComponent) {
		return;
	}
	
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent)) {
		EnhancedInput->BindAction(
			LockInput,
			ETriggerEvent::Triggered,
			this,
			&UCharacterLockControlComponent::OnLockInput
			);
	}
}

void UCharacterLockControlComponent::OnLockInput(const struct FInputActionValue& Value) {
	FVector2D Input = Value.Get<FVector2D>();
	if (ACharacter* CharacterActor = Cast<ACharacter>(GetOwner())) {
		
		if (VerticalSensitivity < 0.0f) {
			VerticalSensitivity = 1.0f;
		}
		
		if (HorizontalSensitivity < 0.0f) {
			HorizontalSensitivity = 1.0f;
		}
		
		CharacterActor->AddControllerYawInput(Input.X * VerticalSensitivity);
		CharacterActor->AddControllerPitchInput(Input.Y * HorizontalSensitivity);
	}
}

bool UCharacterLockControlComponent::GetLookTargetLocation(const float MaxRange, FVector& OutHitLocation) const {
	if (!FollowCamera) {
		return false;
	}
	
	
}


// Called every frame
void UCharacterLockControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

