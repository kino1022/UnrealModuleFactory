// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Weapon/WeaponBase.h"

struct FInteractContext;

#include "FireControlLogic.generated.h"

// ShootSocketName を受け取るDelegateの宣言
DECLARE_MULTICAST_DELEGATE_OneParam(FOnFireDelegate, FName);


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

	// Delegate接続用メソッド（BlueprintCallableから外す）
	void BindFireDelegate(const FOnFireDelegate::FDelegate& InDelegate) {
		OnFireDelegate.Add(InDelegate);
	}

	
protected:
	
	FOnFireDelegate OnFireDelegate;
	
	// 持ち主の武器を取得するヘルパー
	class AWeaponBase* GetWeapon() const
	{
		return Cast<AWeaponBase>(GetOuter());
	}
	
};
