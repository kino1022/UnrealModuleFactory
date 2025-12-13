
// Fill out your copyright notice in the Description page of Project Settings.


#include "Collision/Collision/OnHitGiveEffectCallback.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Collision/BulletHitContext.h"
#include "GameFramework/Character.h"

void UOnHitGiveEffectCallback::ExecuteCallback_Implementation (const FBulletHitContext& HitContext) {
	Super::ExecuteCallback_Implementation(HitContext);
	
	TScriptInterface<IAbilitySystemInterface> AbilitySystemInterface = TScriptInterface<IAbilitySystemInterface>(HitContext.OtherActor);
	if (!AbilitySystemInterface) {
		return;
	}
	UAbilitySystemComponent* AbilitySystem = AbilitySystemInterface->GetAbilitySystemComponent();
	if (AbilitySystem) {
		FGameplayEffectSpecHandle SpecHandle = AbilitySystem->MakeOutgoingSpec(
			EffectClass,
			1.0f,
			AbilitySystem->MakeEffectContext()
			);
		
		//タグが指定されているならCallerに対して値を適用
		if (SpecHandle.IsValid() && EffectCallerTag.IsValid()) {
			SpecHandle.Data.Get()->SetSetByCallerMagnitude(
				EffectCallerTag,
				CallerValue
				);
		}
		
		// 効果を適用
		AbilitySystem->ApplyGameplayEffectSpecToTarget(
			*SpecHandle.Data.Get(),
			AbilitySystem
			);
	}
}