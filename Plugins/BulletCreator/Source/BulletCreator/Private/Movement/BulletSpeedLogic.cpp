// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement/BulletSpeedLogic.h"

void UBulletSpeedLogic::Initialize(ABullet* BulletActor) {
	if (!BulletActor) return;
	PreInitialize(BulletActor);
	Bullet = BulletActor;
	PostInitialize();
}

void UBulletSpeedLogic::Enter_Implementation() {
	
}

void UBulletSpeedLogic::Update_Implementation() {
	
}

void UBulletSpeedLogic::Exit_Implementation() {
	
}

