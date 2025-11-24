// Fill out your copyright notice in the Description page of Project Settings.

#include "Movement/BulletDirectionLogic.h"

void UBulletDirectionLogic::Initialize(ABullet* BulletActor) {
	if (!BulletActor) return;
	PreInitialize(BulletActor);
	Bullet = BulletActor;
	PostInitialize();
}

void UBulletDirectionLogic::Enter_Implementation() {
	
}

void UBulletDirectionLogic::Update_Implementation() {
	
}

void UBulletDirectionLogic::Exit_Implementation() {
	
}

