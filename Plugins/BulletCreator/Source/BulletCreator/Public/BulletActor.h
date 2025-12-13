// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletActor.generated.h"

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLETCREATOR_API ABulletActor : public AActor {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletActor();
	
	UFUNCTION(BlueprintCallable, Category = "BulletActor|Projectile")
	class UProjectileMovementComponent* GetProjectileMovement() const {
		return ProjectileMovement;
	}
	
	UFUNCTION(BlueprintCallable, Category = "BulletActor|Projectile")
	class UBulletRangeRecorder* GetBulletRange () const {
		return RangeRecorder;
	}
	
	UFUNCTION(BlueprintCallable, Category = "BulletActor|Owner")
	void SetOwnerCharacter (class ACharacter* NewOwnerCharacter);
	
	UFUNCTION(BlueprintCallable, Category = "BulletActor|Owner")
	ACharacter* GetOwnerCharacter() const;
	
	UFUNCTION(BlueprintCallable, Category = "BulletActor|Owner")
	UMeshComponent* GetBulletMesh () const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BulletActor|Components")
	TObjectPtr<class USphereComponent> BulletSphere;
	
	/* MeshComponent(見てわかんだろ) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="BulletActor|Components")
	TObjectPtr<UMeshComponent> BulletMesh;
	
	/* ProjectileMovementComponent(なんすかねぇこれ) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BulletActor|Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	
	/* 弾丸の運動を管理するコンポーネント */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="BulletActor|Components")
	TObjectPtr<class UMovementControlComponent> MovementControl;

	/* 弾丸の衝突時の処理を管理・実行するクラス */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="BulletActor|Components")
	TObjectPtr<class UBulletCollisionControlComponent> BulletCollision;
	
	/* 弾丸の飛距離を管理するクラス */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="BulletActor|Components")
	TObjectPtr<class UBulletRangeRecorder> RangeRecorder;
	
	/* 弾丸の持ち主を示す弱参照 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BulletActor|Components")
	TWeakObjectPtr<ACharacter> OwnerCharacter;
	
	UFUNCTION()
	void OnHit (UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
