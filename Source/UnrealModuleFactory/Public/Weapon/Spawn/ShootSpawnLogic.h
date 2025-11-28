// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Weapon/WeaponBase.h"
#include "ShootSpawnLogic.generated.h"

class ABullet;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew)
class UNREALMODULEFACTORY_API UShootSpawnLogic : public UObject
{
	GENERATED_BODY()
	
public:
	
	virtual void OnBulletSpawn (TSubclassOf<ABullet> BulletActor) {}
	
	virtual UWorld* GetWorld () const override {
		// Outer（持ち主）がアクターやコンポーネントなら、そこからワールドをもらう
		if (const UObject* MyOuter = GetOuter())
		{
			return MyOuter->GetWorld();
		}
		return nullptr;
	}
	
protected:
		
	// 持ち主の武器を取得するヘルパー
	AWeaponBase* GetWeapon() const {
		return Cast<AWeaponBase>(GetOuter());
	}
	
};
