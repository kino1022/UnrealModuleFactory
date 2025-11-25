// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MaxHealthComponent.h"
#include "StatusComponent.h"
#include "Components/ActorComponent.h"
#include "HealthStatusComponent.generated.h"

UDELEGATE(BlueprintInternalUseOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeadEvent, AActor*, DeadActor);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STATUSMODULE_API UHealthStatusComponent : public UStatusComponent
{
	GENERATED_BODY()

public:	
	
	// Sets default values for this component's properties
	UHealthStatusComponent();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status Value")
	FOnDeadEvent OnDeadEvent;
	
	virtual void SetStatusValue_Implementation(const float value) override;

protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status Value")
	TScriptInterface<IStatusInterface> MaxHealth;

public:	
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
