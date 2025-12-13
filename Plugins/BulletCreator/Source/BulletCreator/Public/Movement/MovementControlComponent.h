// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovementControlComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BULLETCREATOR_API UMovementControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovementControlComponent();
	
	UFUNCTION(BlueprintCallable, Category="Movement")
	void SetBulletSpeed (const float& Speed);
	
	UFUNCTION(BlueprintCallable, Category="Movement")
	void SetBulletVelocity (const FVector& Velocity);
	
	UFUNCTION(BlueprintNativeEvent, Category="Movement")
	/* 毎フレームの運動量算出前に呼ばれるメソッド */
	void PreCalculateMovement();
	virtual void PreCalculateMovement_Implementation() {}
	
	UFUNCTION(BlueprintNativeEvent, Category="Movement")
	/* 毎フレームの運動量算出後に呼ばれるメソッド */
	void PostCalculateMovement();
	virtual void PostCalculateMovement_Implementation() {}
	
	UFUNCTION(BlueprintNativeEvent, Category="Movement")
	/* 毎フレームの運動量適用前に呼ばれるメソッド */
	void PreApplyMovement ();
	virtual void PreApplyMovement_Implementation() {}
	
	UFUNCTION(BlueprintNativeEvent, Category="Movement")
	void PostApplyMovement ();
	virtual void PostApplyMovement_Implementation() {}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	/* 弾丸の進行する方向 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementControl|Movement")
	FVector BulletMovement;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementControl|Velocity")
	FVector CurrentVelocity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementControl|Speed")
	float CurrentSpeed;
	
	TWeakObjectPtr<class UProjectileMovementComponent> ProjectileMovement;
	
	UFUNCTION()
	FVector CalculateMovement ();

public:	
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
