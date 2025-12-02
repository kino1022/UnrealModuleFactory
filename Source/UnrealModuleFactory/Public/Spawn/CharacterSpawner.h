// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterSpawner.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALMODULEFACTORY_API ACharacterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	
	// Sets default values for this actor's properties
	ACharacterSpawner();
	
	/*
	 * キャラクターをスポーンさせる際の処理
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "Character Spawner")
	void SpawnCharacter ();
	virtual void SpawnCharacter_Implementation();
	
	/*
	 * キャラクターをスポーンさせた後に呼び出される処理
	 * @param SpawnedCharacter スポーンさせたキャラクターの参照
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "Character Spawner")
	void OnAfterSpawn (class ACharacterBase* SpawnedCharacter);
	virtual void OnAfterSpawn_Implementation(ACharacterBase* SpawnedCharacter);
	
	/* スポーン処理の直前に読み込まれる処理 */
	UFUNCTION(BlueprintNativeEvent, Category = "Character Spawner")
	void OnBeforeSpawn ();
	virtual void OnBeforeSpawn_Implementation();
	
	UFUNCTION(BlueprintCallable, Category = "Character Spawner")
	bool SetSpawnCharacter (TSubclassOf<ACharacterBase> NextCharacter);
	
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	/*　スポーンさせるキャラクター */
	UPROPERTY(EditAnywhere, Category = "Character Spawner")
	TSubclassOf<ACharacterBase> Character;

public:	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
