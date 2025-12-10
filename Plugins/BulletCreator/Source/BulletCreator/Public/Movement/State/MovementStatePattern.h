// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Movement/State/PatternTransitionTrigger.h"
#include "MovementStatePattern.generated.h"

class UMovementPatternObject;

/**
 * 状態遷移のルールを定義するデータアセット
 * SpeedPatternまたはVelocityPatternと、次の状態への遷移条件をセットで保持します
 */
USTRUCT(BlueprintType)
struct FPatternTransition {
	GENERATED_BODY()
	
	/* 遷移先の状態パターン */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Transition")
	TObjectPtr<class UMovementStatePattern> NextState;
	
	/* 遷移条件トリガー（複数指定可能、全てtrueで遷移） */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Transition")
	TArray<TSubclassOf<UPatternTransitionTrigger>> TransitionTriggers;
};

/**
 * 移動パターンの状態を定義するデータアセット
 */
UCLASS()
class BULLETCREATOR_API UMovementStatePattern : public UDataAsset {
	GENERATED_BODY()
public:
	
	/* この状態で使用するSpeedPatternのクラス（VelocityPatternと排他的） */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pattern")
	TSubclassOf<class UBulletSpeedPattern> SpeedPatternClass;
	
	/* この状態で使用するVelocityPatternのクラス（SpeedPatternと排他的） */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pattern")
	TSubclassOf<class UBulletVelocityPattern> VelocityPatternClass;
	
	/* この状態からの遷移ルール */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Transition")
	TArray<FPatternTransition> Transitions;
	
	/* 状態の名前（デバッグ用） */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug")
	FString StateName;
};
