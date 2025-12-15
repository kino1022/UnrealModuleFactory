// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BoostAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class UNREALMODULEFACTORY_API UBoostAttributeSet : public UAttributeSet {
	GENERATED_BODY()
public:
	
	UBoostAttributeSet();
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(BlueprintReadOnly, Category = "Boost", ReplicatedUsing = "OnRep_Boost")
	FGameplayAttributeData Boost;
	ATTRIBUTE_ACCESSORS(UBoostAttributeSet, Boost)
	
	UPROPERTY(BlueprintReadOnly, Category = "Boost", ReplicatedUsing = "OnRep_MaxBoost")
	FGameplayAttributeData MaxBoost;
	ATTRIBUTE_ACCESSORS(UBoostAttributeSet, MaxBoost)
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	UFUNCTION()
	virtual void OnRep_Boost(const FGameplayAttributeData& OldBoost);
	
	UFUNCTION()
	virtual void OnRep_MaxBoost(const FGameplayAttributeData& OldMaxBoost);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boost|Effect")
	TSubclassOf<class UGameplayEffect> OverHeatEffectClass;
	
	
};
