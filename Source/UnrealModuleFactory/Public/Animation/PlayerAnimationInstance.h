// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimationInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMODULEFACTORY_API UPlayerAnimationInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Animation Instance")
	bool IsInJump = false;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Animation Instance")
	bool IsInAir = false;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Animation Instance")
	class ACharacterBase* PlayerCharacter;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Character Instance")
	class UCharacterMovementComponent* MovementComponent;
};
