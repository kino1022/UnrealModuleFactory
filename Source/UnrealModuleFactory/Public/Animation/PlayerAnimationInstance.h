// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimationInstance.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
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
	bool IsWalking = false;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Animation Instance")
	float WalkDirection = 0.0f;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Animation Instance")
	float WalkSpeed = 0.0f;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Animation Instance")
	TWeakObjectPtr<class ACharacterBase> PlayerCharacter;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Character Instance")
	TWeakObjectPtr<class UCharacterMovementComponent> MovementComponent;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Character Instance")
	TArray<class UGameplayAbility*> ActiveAbilities;
};
