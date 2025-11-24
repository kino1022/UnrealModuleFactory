#pragma once
#include "Interface/CorrectionValueInterface.h"

UCLASS(Blueprintable)
class UCorrectionValueBase : public UObject {
	
	GENERATED_BODY()
	
public:
	
protected:
	
	///補正値の値
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Correction Value")
	float CorrectionValue;
	///補正値の分類
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Correction Value")
	TScriptInterface<ICorrectionTypeInterface> CorrectionType;
	///補正値が有効かどうか
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Correction Value")
	bool EnableCorrection = false;
	
};
