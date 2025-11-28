// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "WeaponBase.generated.h"

struct FInteractContext;

UCLASS()
class UNREALMODULEFACTORY_API AWeaponBase : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();
	
	virtual void Interact_Implementation(const FInteractContext& Context) override;
	
	virtual bool Interactable_Implementation(FInteractContext& Context, FText& InteractionOutput) override;
	
	/*
	 *InteractionConditionsをもとにして使用可能条件を取得するメソッド
	 */
	UFUNCTION(BlueprintCallable, Category="Weapon Base")
	virtual bool GetInteractableCondition (FInteractContext& Context, FText& InteractText);

	virtual TObjectPtr<class UMeshComponent> GetWeaponMesh () const {
		return WeaponMesh;
	}
	
	virtual AActor* GetWeaponOwnerCharacter () const {
		return OwnerCharacter;
	}
	
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"), Category="Weapon Base")
	UMeshComponent* WeaponMesh;
	
	/*
	 *アタッチされている武器モジュールコンポーネント
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Category="Weapon Base")
	TArray<class UWeaponModuleComponent*> ModuleComponents;
	
	/*
	 * この武器の所有者キャラクター
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Weapon Base")
	TObjectPtr<AActor> OwnerCharacter;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Weapon Base")
	bool OnInputInteract = false;
	
	/*
	 *キャッシュしたIInteractConditionInterfaceの配列
	 */
	TArray<TScriptInterface<class IInteractConditionInterface>> CachedConditions;
	
	/*
	 *キャッシュしたIInteractBehaviourInterfaceの配列
	 */
	TArray<TScriptInterface<class IInteractBehaviourInterface>> CachedBehaviours;
	
	/*
	 *モジュールからIInteractConditionInterfaceを取得するメソッド
	 */
	TArray<TScriptInterface<IInteractConditionInterface>> GetInteractConditions () const;
	
	/*
	 *モジュールからIInteractBehaviourInterfaceを取得するメソッド
	 */
	TArray<TScriptInterface<IInteractBehaviourInterface>> GetInteractBehaviours () const;
	
	/*
	 *IInteractConditionInterfaceの配列を優先度順にソートするメソッド
	 */
	void SortConditionList (TArray<TScriptInterface<IInteractConditionInterface>>& Array) const;
	
	/*
	 *IInteractBehaviourInterfaceの配列を優先度順にソートするメソッド
	 */
	void SortBehaviourList (TArray<TScriptInterface<IInteractBehaviourInterface>>& Array) const;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
