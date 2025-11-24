#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CorrectionValueInterface.generated.h"

class ICorrectionTypeInterface;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCorrectionValueInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *　　
 */
class CORRECTIONMODULE_API ICorrectionValueInterface
{
	
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Correction Value")
	void Initialize();
	virtual void Initialize_Implementation () =0;
	
	///補正値の値を取得する
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Correction Value")
	float GetCorrectionValue() const;
	virtual float GetCorrectionValue_Implementation() const =0;
	
	///補正タイプを取得する
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Correction Value")
	TScriptInterface<ICorrectionTypeInterface> GetCorrectionType() const;
	virtual TScriptInterface<ICorrectionTypeInterface> GetCorrectionType_Implementation() const =0;
	
	///補正値が有効かどうかを取得する
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Correction Value")
	bool IsEnableCorrection () const;
	virtual bool IsEnableCorrection_Implementation () const =0;
	
};
