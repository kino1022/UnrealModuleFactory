// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/ActionAbility.h"
#include "FireActionAbility.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMODULEFACTORY_API UFireActionAbility : public UActionAbility {
	GENERATED_BODY()
	
public:
	
	UFireActionAbility();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

protected:
	
	virtual void FireLoop ();

	/* 銃自体の参照 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FireAction|Weapon")
	TWeakObjectPtr<class AGunWeaponBase> FireWeapon;
	
	/* 銃のメッシュの参照 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FireAction|Muzzle")
	TWeakObjectPtr<UMeshComponent> MuzzleMesh;
	
	/* 射撃する際のマズル */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FireAction|Muzzle", meta = (GetOptions = "GetMuzzleSocketNames"))
	FName MuzzleSocketName;
	
	/* 生成する弾丸のクラス */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FireAction|Bullet")
	TSubclassOf<class ABulletActor> BulletClass;
	
	/* 射撃モーション */
	TObjectPtr<class AnimationMontage> FireMontage;
	
	UFUNCTION()
	TArray<FString> GetMuzzleSocketNames() const;
};
