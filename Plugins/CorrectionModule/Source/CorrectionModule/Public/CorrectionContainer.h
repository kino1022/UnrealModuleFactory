// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/CorrectionTypeInterface.h"
#include "UObject/Object.h"
#include "CorrectionContainer.generated.h"

UDELEGATE(BlueprintInternalUseOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCorrectionValueChanged);

/**
 * 
 */
UCLASS(Blueprintable)
class CORRECTIONMODULE_API UCorrectionContainer  : public UObject, public FTickableGameObject {
	
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
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Correction Type")
	FOnCorrectionValueChanged OnCorrectionValueChanged;
	
	virtual UWorld* GetTickableGameObjectWorld() const override;
	
	virtual TStatId GetStatId() const override;
	
	virtual void Tick(float DeltaTime) override;
	
protected:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Correction Type")
	TArray<TScriptInterface<ICorrectionValueInterface>> CorrectionValues;
	
	///無効な補正値を全て取得する
	TArray<TScriptInterface<ICorrectionValueInterface>> GetDisEnabledCorrectionValues() const;
	
	///任意のタイプの補正値を全て取得する
	TArray<TScriptInterface<ICorrectionValueInterface>> GetAnyTypeCorrections(TScriptInterface<ICorrectionTypeInterface> CorrectionType);
	
	
};
