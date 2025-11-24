#pragma once
#include "CorrectionValueBase.h"
#include "Interface/CorrectionValueInterface.h"

UCLASS(Blueprintable)
class UTimeLimitCorrection : public UCorrectionValueBase, public ICorrectionValueInterface {
	
	GENERATED_BODY()
	
public:
	
	///補正値のタイマーを開始する
	UFUNCTION(BlueprintCallable, Category = "Correction Value")
	void StartTimer ();
	
	///補正値の値と分類を初期化する	
	UFUNCTION(BlueprintCallable, Category = "TimeLimit Correction Value")
	static UTimeLimitCorrection* CreateCorrection (const float value, const float duration, const TScriptInterface<ICorrectionTypeInterface> type) {
		UTimeLimitCorrection* Obj = NewObject<UTimeLimitCorrection>();
		Obj->CorrectionValue = value;
		Obj->CorrectionType = type;
		Obj->EnableCorrection = true;
		Obj->Duration = duration;
		//初期化処理を書き込んでおく
		return Obj;
	}
	
protected:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TimeLimit Correction Value")
	FTimerHandle TimerHandle;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TimeLimit Correction Value")
	float Duration = 5.0f;
	
	///タイマーのカウントが0になった際に発火される処理
	void OnCountZero();
	
};
