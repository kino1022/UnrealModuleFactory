// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/StatusInterface.h"
#include "StatusComponent.generated.h"

UDELEGATE(Blueprintable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStatusChangedEvent);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STATUSMODULE_API UStatusComponent : public UActorComponent, public IStatusInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();
	
	///ステータスの値が変化した際に発火するイベント
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status Value")
	FOnStatusChangedEvent OnStatusChangedEvent;
	
	///値の変化は共通部分のSetStatusValueを通過させること(イベントの発火漏れをなくすため)
	virtual void SetStatusValue_Implementation(const float value) override;
	
	virtual float GetStatusValue_Implementation() const override;
	
	virtual void IncreaseStatusValue_Implementation(const float delta) override;
	
	virtual void DecreaseStatusValue_Implementation(const float delta) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	///ステータスの現在の値
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status Value")
	float CurrentValue = 0.0f;
	
	///マイナスの値を許可するかどうか
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status Value")
	bool AllowMinusValue = false;

public:	
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
