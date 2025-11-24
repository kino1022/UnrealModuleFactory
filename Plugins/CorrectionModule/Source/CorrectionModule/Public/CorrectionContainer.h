// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CorrectionMapEntry.h"
#include "Interface/CorrectionTypeInterface.h"
#include "UObject/Object.h"
#include "CorrectionContainer.generated.h"

/**
 * 
 */
UCLASS()
class CORRECTIONMODULE_API UCorrectionContainer : public UObject
{
	GENERATED_BODY()
	
public:
	
	UCorrectionContainer();
	
	///補正値を適用する
	UFUNCTION(BlueprintCallable, Category = "Correction Type")
	float ApplyCorrection (const float BaseValue);
	
	///補正値を追加する
	UFUNCTION(BlueprintCallable, Category = "Correction Type")
	void AddCorrectionValue (const TScriptInterface<ICorrectionValueInterface> CorrectionValue);
	
	///補正値を削除する
	UFUNCTION(BlueprintCallable, Category = "Correction Type")
	void RemoveCorrectionValue (const TScriptInterface<ICorrectionValueInterface> CorrectionValue);
	
	///全ての補正値をクリアする
	UFUNCTION(BlueprintCallable, Category = "Correction Type")
	void ClearCorrectionValues ();
	
protected:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Correction Type")
	TArray<UCorrectionMapEntry*> CorrectionMap;
	
};
