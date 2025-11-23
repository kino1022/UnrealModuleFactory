// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class BULLETCREATOR_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	UFUNCTION(BlueprintCallable, Category = "Bullet")
	void Initialize(AActor* Owner);

	UFUNCTION(BlueprintImplementableEvent, Category = "Bullet")
	void PreInitialize(AActor* Owner);

	UFUNCTION(BlueprintImplementableEvent, Category = "Bullet")
	void PostInitialize();

	UFUNCTION(BlueprintCallable, Category = "Bullet")
	AActor* GetOwner () {return Owner;}

protected:

	UPROPERTY(EditAnywhere, Category = "Bullet")
	TObjectPtr<AActor> Owner;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
