// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Movement/BulletMovementController.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Bullet.generated.h"

class USphereComponent;

UCLASS(Blueprintable)
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Bullet")
	UBulletMovementController* MovementController;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Bullet")
	UStaticMeshComponent* BulletMesh;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Bullet")
	UProjectileMovementComponent* MovementComponent;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Bullet")
	USphereComponent* CollisionComponent;

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
