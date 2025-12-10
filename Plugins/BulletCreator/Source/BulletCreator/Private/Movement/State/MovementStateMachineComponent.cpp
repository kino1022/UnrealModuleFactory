// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement/State/MovementStateMachineComponent.h"
#include "BulletActor.h"
#include "Movement/State/BulletSpeedPattern.h"
#include "Movement/State/MovementStatePattern.h"
#include "Movement/State/BulletVelocityPattern.h"

void UMovementStateMachineComponent::BeginPlay() {
	Super::BeginPlay();
	
	// BulletActorの取得
	if (AActor* Owner = GetOwner()) {
		BulletActor = Cast<ABulletActor>(Owner);
	}
	
	// 初期状態の設定
	if (InitialStatePattern) {
		InitializeStateMachine(InitialStatePattern);
	}
}

void UMovementStateMachineComponent::InitializeStateMachine(UMovementStatePattern* InitialState) {
	if (!InitialState) {
		UE_LOG(LogTemp, Warning, TEXT("MovementStateMachine: InitialState is null"));
		return;
	}
	
	CurrentState = InitialState;
	TransitionState(InitialState);
}

void UMovementStateMachineComponent::PreCalculateMovement_Implementation() {
	if (TTuple<bool, TObjectPtr<UMovementStatePattern>> TransitionResult = CheckTransitions(); TransitionResult.Key) {
		if (TransitionResult.Value) {
			TransitionState(TransitionResult.Value);
		}
	}
	CurrentSpeed = CalculateSpeed();
	CurrentVelocity = CalculateVelocity();
}

TTuple<bool, TObjectPtr<UMovementStatePattern>> UMovementStateMachineComponent::CheckTransitions() const {
	if (CurrentTransitionPattern.Num() <= 0) {
		return TTuple<bool, TObjectPtr<UMovementStatePattern>>(false, nullptr);
	}
	
	// 各遷移グループごとにチェック（同じNextStateを持つトリガーをグループ化）
	TMap<TObjectPtr<UMovementStatePattern>, TArray<TObjectPtr<UPatternTransitionTrigger>>> TransitionGroups;
	for (const FStateMachineTransitionPattern& TransitionPattern : CurrentTransitionPattern) {
		if (!TransitionPattern.TransitionTrigger || !TransitionPattern.NextState) {
			continue;
		}
		TransitionGroups.FindOrAdd(TransitionPattern.NextState).Add(TransitionPattern.TransitionTrigger);
	}
	
	// 各グループのトリガーが全てtrueかチェック（AND条件）
	for (const auto& Group : TransitionGroups) {
		bool bAllTriggered = true;
		for (const TObjectPtr<UPatternTransitionTrigger>& Trigger : Group.Value) {
			if (!Trigger || !Trigger->IsTriggered()) {
				bAllTriggered = false;
				break;
			}
		}
		if (bAllTriggered) {
			return TTuple<bool, TObjectPtr<UMovementStatePattern>>(true, Group.Key);
		}
	}
	
	return TTuple<bool, TObjectPtr<UMovementStatePattern>>(false, nullptr);
}

float UMovementStateMachineComponent::CalculateSpeed_Implementation () {
	if (!CurrentSpeedPattern) {
		return 0.0f;
	}
	return CurrentSpeedPattern->GetSpeed();
}

FVector UMovementStateMachineComponent::CalculateVelocity_Implementation  () {
	if (!CurrentVelocityPattern) {
		return FVector::ZeroVector;
	}
	return CurrentVelocityPattern->GetVelocity();
}

void UMovementStateMachineComponent::TransitionState (UMovementStatePattern* NextState) {
	
	if (!NextState) {
		return;
	}
	
	// SpeedPatternとVelocityPatternの排他性チェック
	if (NextState->SpeedPatternClass && NextState->VelocityPatternClass) {
		UE_LOG(LogTemp, Warning, TEXT("MovementStateMachine: Both SpeedPattern and VelocityPattern are set in state '%s'. Only SpeedPattern will be used."), *NextState->StateName);
	}
	
	// 古いパターンをクリーンアップ
	CleanupCurrentPatterns();
	
	// 現在の状態を更新
	CurrentState = NextState;
	
	// 新しいパターンを作成
	CurrentSpeedPattern = InstanceSpeedPattern(NextState);
	CurrentVelocityPattern = InstanceVelocityPattern(NextState);
	CurrentTransitionPattern = CreateNewTransitionPattern(NextState);
	
	// 新しいパターンを初期化
	InitializeSpeedPattern(CurrentSpeedPattern);
	InitializeVelocityPattern(CurrentVelocityPattern);
	InitializeTransitionTriggers(CurrentTransitionPattern);
	
}

TObjectPtr<UBulletSpeedPattern> UMovementStateMachineComponent::InstanceSpeedPattern(UMovementStatePattern* StatePattern) {
	if (!StatePattern) {
		return nullptr;
	}
	if (!StatePattern->SpeedPatternClass) {
		return nullptr;
	}
	if (UBulletSpeedPattern* SpeedPattern = NewObject<UBulletSpeedPattern>(this, StatePattern->SpeedPatternClass)) {
		return SpeedPattern;
	}
	return nullptr;
}

TObjectPtr<UBulletVelocityPattern> UMovementStateMachineComponent::InstanceVelocityPattern(UMovementStatePattern* StatePattern) {
	if (!StatePattern) {
		return nullptr;
	}
	if (!StatePattern->VelocityPatternClass) {
		return nullptr;
	}
	if (UBulletVelocityPattern* VelocityPattern = NewObject<UBulletVelocityPattern>(this, StatePattern->VelocityPatternClass)) {
		return VelocityPattern;
	}
	return nullptr;
}

TArray<FStateMachineTransitionPattern> UMovementStateMachineComponent::CreateNewTransitionPattern(UMovementStatePattern* StatePattern) {
	TArray<FStateMachineTransitionPattern> Transitions;
	if (!StatePattern) {
		return Transitions;
	}
	if (StatePattern->Transitions.Num() <= 0) {
		return Transitions;
	}
	for (const FPatternTransition& PatternTransition : StatePattern->Transitions) {
		for (TSubclassOf<UPatternTransitionTrigger> TriggerClass : PatternTransition.TransitionTriggers) {
			if (!TriggerClass) {
				continue;
			}
			UPatternTransitionTrigger* Trigger = NewObject<UPatternTransitionTrigger>(this, TriggerClass);
			if (!Trigger) {
				continue;
			}
			FStateMachineTransitionPattern NewTransition;
			NewTransition.NextState = PatternTransition.NextState;
			NewTransition.TransitionTrigger = Trigger;
			Transitions.Add(NewTransition);
		}
	}
	return Transitions;
}

void UMovementStateMachineComponent::InitializeTransitionTriggers(const TArray<FStateMachineTransitionPattern>& TransitionPatterns) const {
	if (TransitionPatterns.Num() <= 0) {
		return;
	}
	ABulletActor* Bullet = GetBulletActor();
	if (!Bullet) {
		return;
	}
	for (FStateMachineTransitionPattern TransitionPattern : TransitionPatterns) {
		if (TransitionPattern.TransitionTrigger) {
			TransitionPattern.TransitionTrigger->Initialize(Bullet);
		}
	}
}

void UMovementStateMachineComponent::InitializeSpeedPattern(UBulletSpeedPattern* SpeedPattern) {
	if (!SpeedPattern) {
		return;
	}
	ABulletActor* Bullet = GetBulletActor();
	if (!Bullet) {
		return;
	}
	SpeedPattern->Initialize(Bullet);
}

void UMovementStateMachineComponent::InitializeVelocityPattern(UBulletVelocityPattern* VelocityPattern) {
	if (!VelocityPattern) {
		return;
	}
	ABulletActor* Bullet = GetBulletActor();
	if (!Bullet) {
		return;
	}
	VelocityPattern->Initialize(Bullet);
}

ABulletActor* UMovementStateMachineComponent::GetBulletActor() const {
	if (!BulletActor.IsValid()) {
		return nullptr;
	}
	if (ABulletActor* Bullet = BulletActor.Get()) {
		return Bullet;
	}
	return nullptr;
}

void UMovementStateMachineComponent::CleanupCurrentPatterns() {
	// 古いトリガーのクリーンアップ
	for (FStateMachineTransitionPattern& TransitionPattern : CurrentTransitionPattern) {
		if (TransitionPattern.TransitionTrigger) {
			TransitionPattern.TransitionTrigger->MarkAsGarbage();
			TransitionPattern.TransitionTrigger = nullptr;
		}
	}
	CurrentTransitionPattern.Empty();
	
	// 古いSpeedPatternのクリーンアップ
	if (CurrentSpeedPattern) {
		CurrentSpeedPattern->MarkAsGarbage();
		CurrentSpeedPattern = nullptr;
	}
	
	// 古いVelocityPatternのクリーンアップ
	if (CurrentVelocityPattern) {
		CurrentVelocityPattern->MarkAsGarbage();
		CurrentVelocityPattern = nullptr;
	}
}
