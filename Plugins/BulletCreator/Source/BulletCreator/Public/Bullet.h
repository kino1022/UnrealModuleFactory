// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Movement/BulletMovementController.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Bullet.generated.h"

class USphereComponent;

UCLASS()
class BULLETCREATOR_API ABullet : public AActor {
	
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	UFUNCTION(BlueprintCallable, Category = "Bullet")
	void Initialize(AActor* InOwner);

	UFUNCTION(BlueprintImplementableEvent, Category = "Bullet")
	void PreInitialize(AActor* InOwner);

	UFUNCTION(BlueprintImplementableEvent, Category = "Bullet")
	void PostInitialize();

	UFUNCTION(BlueprintCallable, Category = "Bullet")
	AActor* GetOwnerActor () {return OwnerActor;}

protected:

	UPROPERTY(VisibleAnywhere, Category = "Bullet")
	TObjectPtr<AActor> OwnerActor;
	
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,Category = "Bullet")
	TObjectPtr<UBulletMovementController> MovementController;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Bullet")
	UStaticMeshComponent* BulletMesh;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Bullet")
	UProjectileMovementComponent* MovementComponent;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Bullet")
	USphereComponent* CollisionComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
