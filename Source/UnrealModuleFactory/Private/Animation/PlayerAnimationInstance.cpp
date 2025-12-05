// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerAnimationInstance.h"
#include "Public/Character/CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAnimationInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	if (APawn* OwningPawn = TryGetPawnOwner()) {
		PlayerCharacter = Cast<ACharacterBase>(OwningPawn);
		if (PlayerCharacter) {
			MovementComponent = PlayerCharacter->GetCharacterMovement();
		}
	}
}

void UPlayerAnimationInstance::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (MovementComponent) {
		IsInAir = MovementComponent->IsFalling();
		IsInJump = MovementComponent->IsFlying();
	}
	
	if (PlayerCharacter) {
		if (UActionAbilitySystemComponent* ASC = Cast<UActionAbilitySystemComponent>(PlayerCharacter->GetAbilitySystemComponent())) {
			ASC->GetActiveAbilities(ActiveAbilities);
		}
	}
}