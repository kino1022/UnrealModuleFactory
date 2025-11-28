// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Weapon/WeaponBase.h"
#include "Weapon/Shoot/ShootBulletModuleComponent.h"
#include "FireControlLogic.generated.h"

struct FInteractContext;

/**
 * 
 */
UCLASS(Abstract, EditInlineNew, Blueprintable)
class UNREALMODULEFACTORY_API UFireControlLogic : public UObject
{
	GENERATED_BODY()
	
public:
	
	/*
	 *　射撃入力が始まった際に呼ばれるメソッド
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Fire Control Logic")
	void OnStartFire ();
	virtual void OnStartFire_Implementation() {}
	
	/*
	 *　射撃入力が止まった際に呼ばれるメソッド
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Fire Control Logic")
	void OnStopFire ();
	virtual void OnStopFire_Implementation() {}
	
	/*
	 *　射撃入力時に毎フレーム呼ばれるメソッド
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Fire Control Logic")
	void OnTickFire (float DeltaTime);
	virtual void OnTickFire_Implementation (float DeltaTime) {}
	
	virtual UWorld* GetWorld () const override {
		// Outer（持ち主）がアクターやコンポーネントなら、そこからワールドをもらう
		if (const UObject* MyOuter = GetOuter())
		{
			return MyOuter->GetWorld();
		}
		return nullptr;
	}
	
	UFUNCTION(BlueprintCallable, Category = "Fire Control Logic")
	void SetFireDelegate (const TDelegate<void ()>& Delegate) {
		OnFireDelegate = Delegate;
	}

	
protected:
	
	TDelegate<void ()> OnFireDelegate;
	
	// 持ち主の武器を取得するヘルパー
	class AWeaponBase* GetWeapon() const
	{
		return Cast<AWeaponBase>(GetOuter());
	}
	
};
