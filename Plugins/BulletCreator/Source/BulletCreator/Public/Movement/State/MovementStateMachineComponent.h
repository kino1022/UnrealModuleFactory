// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Movement/MovementControlComponent.h"
#include "Templates/Tuple.h"
#include "MovementStateMachineComponent.generated.h"

/**
 * MovementStateMachine内で利用する遷移条件と遷移先の管理構造体
 */
USTRUCT(BlueprintType, Blueprintable)
struct FStateMachineTransitionPattern {
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	TObjectPtr<class UPatternTransitionTrigger> TransitionTrigger;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	TObjectPtr<class UMovementStatePattern> NextState;
};

/**
 * 
 */
UCLASS()
class BULLETCREATOR_API UMovementStateMachineComponent : public UMovementControlComponent {
	GENERATED_BODY()
public:
	
	virtual void BeginPlay() override;
	
	virtual void PreCalculateMovement_Implementation() override;
	
	UFUNCTION(BlueprintCallable, Category="Movement")
	void InitializeStateMachine(UMovementStatePattern* InitialState);
	
	UFUNCTION(BlueprintNativeEvent, Category="Movement")
	float CalculateSpeed ();
	virtual float CalculateSpeed_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, Category="Movement")
	FVector CalculateVelocity ();
	virtual FVector CalculateVelocity_Implementation();
	
	UFUNCTION(BlueprintCallable, Category="Movement")
	void TransitionState (UMovementStatePattern* NextState);
	
	TTuple<bool, TObjectPtr<UMovementStatePattern>> CheckTransitions() const;
	
protected:
	
	TWeakObjectPtr<class ABulletActor> BulletActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	TObjectPtr<UMovementStatePattern> InitialStatePattern;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	TObjectPtr<UMovementStatePattern> CurrentState;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	TObjectPtr<class UBulletSpeedPattern> CurrentSpeedPattern;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	TObjectPtr<class UBulletVelocityPattern> CurrentVelocityPattern;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	TArray<FStateMachineTransitionPattern> CurrentTransitionPattern;
	
	TObjectPtr<UBulletSpeedPattern> InstanceSpeedPattern(UMovementStatePattern* StatePattern);
	
	TObjectPtr<UBulletVelocityPattern> InstanceVelocityPattern(UMovementStatePattern* StatePattern);
	
	TArray<FStateMachineTransitionPattern> CreateNewTransitionPattern(UMovementStatePattern* StatePattern);
	
	void InitializeTransitionTriggers(const TArray<FStateMachineTransitionPattern>& TransitionPatterns) const;
	
	void InitializeSpeedPattern(UBulletSpeedPattern* SpeedPattern);
	
	void InitializeVelocityPattern(UBulletVelocityPattern* VelocityPattern);
	
	void CleanupCurrentPatterns();
	
	ABulletActor* GetBulletActor() const;
		
};


