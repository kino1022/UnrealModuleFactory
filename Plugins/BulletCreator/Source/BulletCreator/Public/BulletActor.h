// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletActor.generated.h"

UCLASS()
class BULLETCREATOR_API ABulletActor : public AActor {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletActor();
	
	UFUNCTION(BlueprintCallable, Category = "BulletActor|Projectile")
	class UProjectileMovementComponent* GetProjectileMovement() const {
		return ProjectileMovement;
	}
	
	UFUNCTION(BlueprintCallable, Category = "BulletActor|Owner")
	void SetOwnerCharacter (class ACharacter* NewOwnerCharacter);
	
	UFUNCTION(BlueprintCallable, Category = "BulletActor|Owner")
	class ACharacter* GetOwnerCharacter() const;
	
	UFUNCTION(BlueprintCallable, Category = "BulletActor|Owner")
	UMeshComponent* GetBulletMesh () const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BulletActor|Components")
	TObjectPtr<class USphereComponent> BulletSphere;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="BulletActor|Components")
	TObjectPtr<UMeshComponent> BulletMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BulletActor|Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="BulletActor|Components")
	TObjectPtr<class UMovementControlComponent> MovementControl;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="BulletActor|Components")
	TObjectPtr<class UBulletCollisionControlComponent> BulletCollision;
	
	/* 弾丸の持ち主を示す弱参照 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BulletActor|Components")
	TWeakObjectPtr<ACharacter> OwnerCharacter;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
