#pragma once
#include "Interface/CorrectionTypeInterface.h"
#include "CorrectionMapEntry.generated.h"

UCLASS(BlueprintType)
class UCorrectionMapEntry : public UObject {
	
	GENERATED_BODY()
	
public:
	
	UCorrectionMapEntry(){}
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Correction Type")
	TScriptInterface<ICorrectionTypeInterface> CorrectionType;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Correction Type")
	TArray<TScriptInterface<ICorrectionValueInterface>> CorrectionValues;
	
	bool operator==(const TScriptInterface<ICorrectionTypeInterface>& OtherKey) const {
		return CorrectionType == OtherKey;
	}
	
};
