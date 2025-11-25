#pragma once

#include "CoreMinimal.h"
#include "CharacterInitData.generated.h"

USTRUCT(BlueprintType)
struct FCharacterInitData {
	
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character Init Data")
	float MaxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character Init Data")
	float InitialHealth;
	
	
};
