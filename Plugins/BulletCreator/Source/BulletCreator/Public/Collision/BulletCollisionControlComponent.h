// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BulletCollisionControlComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BULLETCREATOR_API UBulletCollisionControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBulletCollisionControlComponent();

	UFUNCTION()
	void OnHit (const struct FBulletHitContext& HitContext);
	
	UFUNCTION(BlueprintCallable, Category = "Collision|Hit")
	bool AddHitCallback (class UBulletCollisionCallback* SetCallback);

	UFUNCTION(BlueprintCallable, Category = "Collision|Hit")
	bool RemoveHitCallback (UBulletCollisionCallback* RemoveCallback);
	
	UFUNCTION(BlueprintCallable, Category = "Collision|Hit")
	void ClearHitCallbacks ();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Collision|Hit")
	TArray<TObjectPtr<UBulletCollisionCallback>> HitCallbacks;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
