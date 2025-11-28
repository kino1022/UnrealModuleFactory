// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractBehaviourInterface.generated.h"

struct FInteractContext;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractBehaviourInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREALMODULEFACTORY_API IInteractBehaviourInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	/*
	 * 使用入力がなされたタイミングで呼ばれる処理
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact Condition")
	void StartInteract (FInteractContext& Context);
	virtual void StartInteract_Implementation (FInteractContext& Context) =0;
	
	/*
	 * 使用入力がキャンセルされたタイミングで呼び出される処理
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact Condition")
	void CancelInteract (FInteractContext& Context);
	virtual void CancelInteract_Implementation (FInteractContext& Context) =0;
	
	/*
	 * 使用入力がされている間に呼ばれ続ける処理
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact Condition")
	void TickInteract (float DeltaTime, FInteractContext& Context);
	virtual void TickInteract_Implementation (float DeltaTime, FInteractContext& Context) =0;
	
	/*
	 * この挙動の優先度を取得する
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact Condition")
	int GetBehaviourPriority ();
	virtual int GetBehaviourPriority_Implementation () =0;
	
	/*
	 * この挙動の優先度を設定する
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact Condition")
	void SetBehaviourPriority (int NewPriority);
	virtual void SetBehaviourPriority_Implementation (int NewPriority) =0;
};
