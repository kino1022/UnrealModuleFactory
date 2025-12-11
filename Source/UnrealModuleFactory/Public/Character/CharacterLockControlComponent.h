// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterLockControlComponent.generated.h"

USTRUCT(BlueprintType)
struct FLookTargetContext {
	GENERATED_BODY()
public:
	/* 視点の先に何らかのオブジェクトが存在したか */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bHit;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALMODULEFACTORY_API UCharacterLockControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterLockControlComponent();

	UFUNCTION(BlueprintCallable, Category = "Look|Interact")
	bool GetLookTargetLocation (const float MaxRange, FVector& OutHitLocation) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	virtual void SetupInput(UInputComponent* InputComponent);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Look|Camera")
	TObjectPtr<class UCameraComponent> FollowCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lock|Input")
	TObjectPtr<class UInputAction> LockInput;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lock|Sensitivity")
	float VerticalSensitivity = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lock|Sensitivity")
	float HorizontalSensitivity = 1.0f;
	
	void OnLockInput (const struct FInputActionValue& Value);
	


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
