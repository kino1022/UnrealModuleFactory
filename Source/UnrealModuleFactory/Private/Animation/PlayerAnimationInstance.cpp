// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerAnimationInstance.h"
#include "Action/ActionAbilitySystemComponent.h"
#include "Public/Character/CharacterBase.h"
#include "KismetAnimationLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAnimationInstance::NativeInitializeAnimation(){
	Super::NativeInitializeAnimation();
	
	if (APawn* OwningPawn = TryGetPawnOwner()) {
		PlayerCharacter = Cast<ACharacterBase>(OwningPawn);
		if (PlayerCharacter.IsValid()) {
			MovementComponent = PlayerCharacter->GetCharacterMovement();
		}
	}
}

void UPlayerAnimationInstance::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (MovementComponent.IsValid()) {
		
		IsWalking = MovementComponent->IsWalking() && MovementComponent->Velocity.Size() > 0.1f;
		
		if (IsWalking) {
			WalkDirection = UKismetAnimationLibrary::CalculateDirection(MovementComponent->Velocity, PlayerCharacter->GetActorRotation());
			WalkSpeed = MovementComponent->GetMaxSpeed();
		}
		else {
			WalkDirection = UKismetAnimationLibrary::CalculateDirection(MovementComponent->Velocity, PlayerCharacter->GetActorRotation());
			WalkSpeed = 0.0f;
		}
		
		IsInAir = MovementComponent->IsFalling();
		
		IsInJump = MovementComponent->IsFlying();
		
	}
	
	if (PlayerCharacter.IsValid()) {
		if (UActionAbilitySystemComponent* ASC = Cast<UActionAbilitySystemComponent>(PlayerCharacter->GetAbilitySystemComponent())) {
			ASC->GetActiveAbilities(ActiveAbilities);
		}
	}
}