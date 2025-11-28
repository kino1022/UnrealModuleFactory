// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

struct FInteractContext;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREALMODULEFACTORY_API IInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	/**
	 * 使用可能かどうかを返すメソッド
	 * @param Context 使用コンテキスト情報
	 * @param InteractionOutput 使用時の出力テキスト
	 * @return 使用可能かどうか
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interact Context")
	bool Interactable (FInteractContext& Context, FText& InteractionOutput);
	virtual bool Interactable_Implementation (FInteractContext& Context, FText& InteractionOutput) =0;
	
	/**
	 * オブジェクトを使用するメソッド
	 * @param Context 使用コンテキスト情報
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interact Context")
	void Interact (const FInteractContext& Context);
	virtual void Interact_Implementation (const FInteractContext& Context) =0;
	
};
