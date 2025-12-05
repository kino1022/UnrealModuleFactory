// Fill out your copyright notice in the Description page of Project Settings.

#include "Action/MoveActionAttributeSet.h"
#include "AttributeSet.h"
#include "GameplayAbilities/Public/GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UMoveActionAttributeSet::UMoveActionAttributeSet() {
	
}

void UMoveActionAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) {
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetMoveSpeedAttribute())
	{
		// オーナーキャラクターを取得
		ACharacter* OwningCharacter = Cast<ACharacter>(GetOwningActor());
		if (OwningCharacter && OwningCharacter->GetCharacterMovement())
		{
			// Attributeの値を、実際の移動コンポーネントの MaxWalkSpeed に適用
			// GetMoveSpeed() は現在の最終値（Base + バフ - デバフ）を取得します
			OwningCharacter->GetCharacterMovement()->MaxWalkSpeed = GetMoveSpeed();
		}
	}
}

void UMoveActionAttributeSet::OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMoveActionAttributeSet, MoveSpeed, OldMoveSpeed);
}