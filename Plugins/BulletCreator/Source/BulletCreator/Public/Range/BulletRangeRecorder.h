// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BulletRangeRecorder.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BULLETCREATOR_API UBulletRangeRecorder : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBulletRangeRecorder();
	
	UFUNCTION(BlueprintCallable, Category = "Bullet|Range")
	float& GetTraveledDistance() {
		return TraveledDistance;
	}

protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;
	
	/* 弾丸が移動した距離を記録する変数 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet|Range")
	float TraveledDistance;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet|Range")
	FVector OriginLocation;
	
	void UpdateTraveledDistance ();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
