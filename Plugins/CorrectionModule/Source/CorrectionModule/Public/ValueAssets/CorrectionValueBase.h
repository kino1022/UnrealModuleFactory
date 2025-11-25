#pragma once
#include "Interface/CorrectionValueInterface.h"
#include "CorrectionValueBase.generated.h"

UCLASS(Blueprintable)
class UCorrectionValueBase : public UObject, public ICorrectionValueInterface {
	
	GENERATED_BODY()
	
public:

	virtual float GetCorrectionValue_Implementation() const override {
		return CorrectionValue;
	}
	
	virtual TScriptInterface<ICorrectionTypeInterface> GetCorrectionType_Implementation() const override {
		return CorrectionType;
	}
	
	virtual bool IsEnableCorrection_Implementation() const override {
		return EnableCorrection;
	}
	
	virtual void Initialize_Implementation() override {}
	
protected:
	
	///補正値の値
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Correction Value")
	float CorrectionValue = 0.0f;
	///補正値の分類
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Correction Value")
	TScriptInterface<ICorrectionTypeInterface> CorrectionType;
	///補正値が有効かどうか
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Correction Value")
	bool EnableCorrection = false;
	
};
