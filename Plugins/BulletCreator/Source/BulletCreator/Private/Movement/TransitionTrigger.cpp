// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement/TransitionTrigger.h"

void UTransitionTrigger::Initialize(ABullet* InOwner) {
	PreInitialize(InOwner);
	OwnerActor = InOwner;
	PostInitialize();
}
