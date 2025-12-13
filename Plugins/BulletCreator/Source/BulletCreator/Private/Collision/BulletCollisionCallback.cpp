// Fill out your copyright notice in the Description page of Project Settings.


#include "Collision/BulletCollisionCallback.h"

#include "Collision/BulletHitContext.h"

void UBulletCollisionCallback::ExecuteCallback_Implementation (const FBulletHitContext& HitContext) {
	//衝突したアクターが存在しないなら処理を中断
	if (!HitContext.OtherActor) {
		return;
	}
	//弾丸が存在しないなら処理を中断
	if (!HitContext.BulletActor) {
		return;
	}
}
