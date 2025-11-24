// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement/MovementState.h"

void UMovementState::InitializeState(ABullet* InOwner) {
	
	if (!InOwner) return;
	
	if (SpeedLogic) {
		SpeedLogic->Initialize(InOwner);
	}
	
	if (DirectionLogic) {
		DirectionLogic->Initialize(InOwner);
	}
	
	TArray<UTransitionTrigger*> Conditions;
	TransitionMap.GetKeys(Conditions);
	
	for (auto& Condition : Conditions) {
		if (!Condition) continue;
		Condition->Initialize(InOwner);
	}
	
}
