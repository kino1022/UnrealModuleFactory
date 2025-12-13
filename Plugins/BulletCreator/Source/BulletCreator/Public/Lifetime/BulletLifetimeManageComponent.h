// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BulletLifetimeManageComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BULLETCREATOR_API UBulletLifetimeManageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBulletLifetimeManageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bullet|Lifetime")
	TArray<TObjectPtr<class UBulletLifetime>> LifetimePolicies;

	UFUNCTION(BlueprintCallable, Category = "Bullet|Lifetime")
	bool CalculateShouldDespawn () const;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
