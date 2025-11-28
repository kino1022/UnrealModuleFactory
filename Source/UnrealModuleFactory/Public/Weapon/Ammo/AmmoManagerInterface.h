// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AmmoManagerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAmmoManagerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREALMODULEFACTORY_API IAmmoManagerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	/*
	 * 最大の弾数を取得する
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UsuallyReloadComponent")
	int GetMaxAmmo () const;
	virtual int GetMaxAmmo_Implementation () const =0;
	
	/*
	 * 最大の弾数をセットする
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UsuallyReloadComponent")
	void SetMaxAmmo (const int MaxAmmo);
	virtual void SetMaxAmmo_Implementation (int Ammo);
	
	/*
	 *残りの弾数を取得する
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Ammo Manager")
	int GetAmmo () const;
	virtual int GetAmmo_Implementation () const =0;
	
	/*
	 * 弾数の値をセットする
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Ammo Manager")
	void SetAmmo (int Ammo);
	virtual void SetAmmo_Implementation (int Ammo) =0;
};
