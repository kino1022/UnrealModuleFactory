#pragma once

#include "CoreMinimal.h"
#include "BulletActor.h"
#include "BulletHitContext.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FBulletHitContext {
	GENERATED_BODY()
public:
	
	UPROPERTY()
	AActor* OtherActor;
	
	UPROPERTY()
	ABulletActor* BulletActor;

	UPROPERTY()
	UPrimitiveComponent* OtherComp;

	UPROPERTY()
	FVector NormalImpulse;

	UPROPERTY()
	FHitResult Hit;
	
};
