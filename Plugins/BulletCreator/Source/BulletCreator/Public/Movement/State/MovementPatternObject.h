// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MovementPatternObject.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class BULLETCREATOR_API UMovementPatternObject : public UObject , public FTickableGameObject {
	GENERATED_BODY()
public:
	
	UMovementPatternObject();
	
	UFUNCTION(BlueprintCallable, Category = "BulletSpeed")
	void Initialize(class ABulletActor* OwnerActor);
	
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintNativeEvent, Category = "BulletSpeed")
	void PreInitialize(ABulletActor* OwnerActor);
	virtual void PreInitialize_Implementation(ABulletActor* OwnerActor) {}
	
	UFUNCTION(BlueprintNativeEvent, Category = "BulletSpeed")
	void PostInitialize();
	virtual void PostInitialize_Implementation() {}
	
	UFUNCTION(BlueprintNativeEvent, Category = "BulletVelocity")
	void Update(float DeltaTime);
	virtual void Update_Implementation(float DeltaTime) {}
	
	UFUNCTION(BlueprintNativeEvent, Category = "BulletVelocity")
	void PreUpdate(float DeltaTime);
	virtual void PreUpdate_Implementation(float DeltaTime) {}
	
	UFUNCTION(BlueprintNativeEvent, Category = "BulletVelocity")
	void PostUpdate(float DeltaTime);
	virtual void PostUpdate_Implementation(float DeltaTime) {}
	
	// プロファイリング用のIDを取得（必須）
	virtual TStatId GetStatId() const override;

	// どのワールドでTickするか（PIE/Game/Editorなど）を判定するのに重要
	virtual UWorld* GetTickableGameObjectWorld() const override;
	
protected:
		
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "BulletSpeed")
	TWeakObjectPtr<ABulletActor> BulletActor;
	
};
