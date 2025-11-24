// Fill out your copyright notice in the Description page of Project Settings.


#include "CorrectionContainer.h"

UCorrectionContainer::UCorrectionContainer() {
	
}

float UCorrectionContainer::ApplyCorrection (const float BaseValue) {
	
	float Result = BaseValue;
	
	TArray<TScriptInterface<ICorrectionTypeInterface>> Types;
	
	///すべての補正値の分類を取得
	for (auto Value : CorrectionValues) {
		//パフォーマンスのために補正値分類を先に取得
		TScriptInterface<ICorrectionTypeInterface> ValueType = ICorrectionValueInterface::Execute_GetCorrectionType(Value.GetObject());
		
		//分類のない不完全な補正値は検知して除外してスキップ
		if (ValueType.GetObject() == nullptr) {
			RemoveCorrectionValue(Value.GetObject());
			continue;
		}
		//すでに取得済みの分類ならスキップ
		if (Types.Contains(ValueType)) {
			continue;
		}
		//新しい分類を追加
		Types.Add(ValueType);
	}
	
	//優先度の高い順にソート
	Types.Sort([](const TScriptInterface<ICorrectionTypeInterface> A, const TScriptInterface<ICorrectionTypeInterface> B) {
		return ICorrectionTypeInterface::Execute_GetPriority(A.GetObject()) > ICorrectionTypeInterface::Execute_GetPriority(B.GetObject());
	});
	
	for (auto Type : Types) {
		TArray<TScriptInterface<ICorrectionValueInterface>> Values = GetAnyTypeCorrections(Type);
		//該当する補正値がなかった場合(ないはずだけど)スキップ
		if (Values.Num() == 0) {
			continue;
		}
		
		Result = ICorrectionTypeInterface::Execute_ApplyCorrection(Type.GetObject(), Result, Values);
	}
	
	return Result;
}

void UCorrectionContainer::AddCorrectionValue (const TScriptInterface<ICorrectionValueInterface> CorrectionValue) {
	if (CorrectionValue.GetObject() == nullptr) {
		return;
	}
	
	CorrectionValues.Add(CorrectionValue);
	OnCorrectionValueChanged.Broadcast();
}

void UCorrectionContainer::RemoveCorrectionValue (const TScriptInterface<ICorrectionValueInterface> CorrectionValue) {
	//nullチェック
	if (CorrectionValues.Num() == 0 || CorrectionValue.GetObject() == nullptr) {
		return;
	}
	
	//補正値を配列から削除
	auto result = CorrectionValues.Remove(CorrectionValue);
	//除去されていたなら補正値の変化を通知
	if (result > 0) {
		OnCorrectionValueChanged.Broadcast();
	}
}

void UCorrectionContainer::ClearCorrectionValues () {
	if (CorrectionValues.Num() == 0) {
		return;
	}
	
	CorrectionValues.Empty();
	OnCorrectionValueChanged.Broadcast();
}

void UCorrectionContainer::Tick(float DeltaTime) {

	//有効ではない補正値の除外処理
	TArray<TScriptInterface<ICorrectionValueInterface>> DisEnable = GetDisEnabledCorrectionValues();
	if (DisEnable.Num() != 0) {
		for (const auto Value : DisEnable) {
			RemoveCorrectionValue(Value);
		}
	}
	
}

TArray<TScriptInterface<ICorrectionValueInterface>> UCorrectionContainer::GetDisEnabledCorrectionValues() const {
	
	if (CorrectionValues.Num() == 0) {
		return TArray<TScriptInterface<ICorrectionValueInterface>>();
	}
	
	TArray<TScriptInterface<ICorrectionValueInterface>> Results;
	
	//ここのループ内で補正値が無効なものをResultsに追加する
	for (const TScriptInterface<ICorrectionValueInterface> Value : CorrectionValues) {
		
		if (Value.GetObject() == nullptr) {
			continue;
		}
		
		if (!ICorrectionValueInterface::Execute_IsEnableCorrection(Value.GetObject())) {
			Results.Add(Value);
		}
	}
	
	return Results;
}

TArray<TScriptInterface<ICorrectionValueInterface>> UCorrectionContainer::GetAnyTypeCorrections(TScriptInterface<ICorrectionTypeInterface> CorrectionType) {
	
	if (CorrectionType.GetObject() == nullptr || CorrectionValues.Num() == 0) {
		return TArray<TScriptInterface<ICorrectionValueInterface>>();
	}
	
	TArray<TScriptInterface<ICorrectionValueInterface>> Results;
	
	for (const TScriptInterface<ICorrectionValueInterface> Value : CorrectionValues) {
		//nullな補正値は除外してスキップ
		if (Value.GetObject() == nullptr) {
			RemoveCorrectionValue(Value);
			continue;
		}
		
		//分類の一致した補正値を結果に加える
		if (ICorrectionValueInterface::Execute_GetCorrectionType(Value.GetObject()) == CorrectionType) {
			Results.Add(Value);
		}
	}
	
	return Results;
}

TStatId UCorrectionContainer::GetStatId() const {
	RETURN_QUICK_DECLARE_CYCLE_STAT(UCorrectionContainer, STATGROUP_Tickables);
}

UWorld* UCorrectionContainer::GetTickableGameObjectWorld() const {
	return GetWorld();
}
