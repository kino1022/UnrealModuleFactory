#pragma once

#include "CoreMinimal.h"
#include "CorrectionValueInterface.h"
#include "UObject/Interface.h"
#include "CorrectionTypeInterface.generated.h"

class ICorrectionValueInterface;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCorrectionTypeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CORRECTIONMODULE_API ICorrectionTypeInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Correction Type")
	int32 GetPriority () const;
	virtual int32 GetPriority_Implementation () const { return 0; }
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Correction Type")
	float ApplyCorrection (const float BaseValue, const TArray<TScriptInterface<ICorrectionValueInterface>> Corrections);
	virtual float ApplyCorrection_Implementation (const float BaseValue, const TArray<TScriptInterface<ICorrectionValueInterface>> Corrections) { return BaseValue; }
	
};
