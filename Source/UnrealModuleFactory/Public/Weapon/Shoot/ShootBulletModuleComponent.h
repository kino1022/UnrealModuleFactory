// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Public/Weapon/Interface/InteractBehaviourInterface.h"
#include "Weapon/FireControl/FireControlLogic.h"
#include "Weapon/WeaponModuleComponent.h"
#include "Weapon/Spawn/ShootSpawnLogic.h"
#include "ShootBulletModuleComponent.generated.h"

struct FInteractContext;

// ShootSocketName を受け取るDelegateの宣言
DECLARE_MULTICAST_DELEGATE_OneParam(FOnFireDelegate, FName);

/**
 * 
 */
UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent), ClassGroup = (WeaponModule), BlueprintType)
class UNREALMODULEFACTORY_API UShootBulletModuleComponent : public UWeaponModuleComponent, public IInteractBehaviourInterface
{
	GENERATED_BODY()
	
public:
	
	UShootBulletModuleComponent();
	
	virtual void BeginPlay() override;
	
	virtual void StartInteract_Implementation(FInteractContext& Context) override;
	
	virtual void CancelInteract_Implementation(FInteractContext& Context) override;
	
	virtual void TickInteract_Implementation(float DeltaTime, FInteractContext& Context) override;
	
	virtual int GetBehaviourPriority_Implementation() override { return BehaviourPriority; }
	
	virtual void SetBehaviourPriority_Implementation(int NewPriority) override;
	
	/*
	 * 実際の射撃の動作を呼び出すメソッド
	 */
	virtual void OnFire(FName SocketName);
	
protected:
	
	FOnFireDelegate OnFireDelegate;
	
	/*
	 *発射する弾丸のアクタークラス
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shoot Bullet")
	TSubclassOf<ABullet> BulletActor;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shoot Bullet", meta = (GetOptions = "GetSocketNameOptions"))
	FName ShootSocketName = "Muzzle";
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shoot Bullet", meta = (AllowPrivateAccess = "True"))
	UFireControlLogic* FireControlLogic;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shoot Bullet", meta = (AllowPrivateAccess = "True"))
	UShootSpawnLogic* ShootSpawnLogic;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Shoot Bullet")
	TArray<FString> GetSocketNameOptions () const;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shoot Bullet")
	int BehaviourPriority = 0;
};
