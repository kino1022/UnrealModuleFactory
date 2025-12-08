// Fill out your copyright notice in the Description page of Project Settings.

#include "Action/MoveActionAttributeSet.h"
#include "AttributeSet.h"
#include "GameplayAbilities/Public/GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

UMoveActionAttributeSet::UMoveActionAttributeSet() {
	
}


// Generated.h に宣言されている仮想関数を実装
void UMoveActionAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UMoveActionAttributeSet, MoveSpeed, COND_None, REPNOTIFY_Always);
}

void UMoveActionAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) {
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetMoveSpeedAttribute()) {
		if (NewValue < 0.0f) {
			NewValue = 0.0f; // 移動速度は負の値にならないようにする
		}
	}
	
	if (Attribute == GetJumpForceAttribute()) {
		if (NewValue < 0.0f) {
			NewValue = 0.0f; // ジャンプ力は負の値にならないようにする
		}
	}
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
	
	if (Data.EvaluatedData.Attribute == GetJumpForceAttribute())
	{
		// オーナーキャラクターを取得
		ACharacter* OwningCharacter = Cast<ACharacter>(GetOwningActor());
		if (OwningCharacter && OwningCharacter->GetCharacterMovement())
		{
			// Attributeの値を、実際の移動コンポーネントの JumpZVelocity に適用
			OwningCharacter->GetCharacterMovement()->JumpZVelocity = GetJumpForce();
		}
	}
}

void UMoveActionAttributeSet::OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMoveActionAttributeSet, MoveSpeed, OldMoveSpeed);
}

void UMoveActionAttributeSet::OnRep_JumpForce(const FGameplayAttributeData& OldJumpForce) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMoveActionAttributeSet, JumpForce, OldJumpForce);
}