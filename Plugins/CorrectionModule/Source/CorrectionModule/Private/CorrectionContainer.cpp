// Fill out your copyright notice in the Description page of Project Settings.


#include "CorrectionContainer.h"

UCorrectionContainer::UCorrectionContainer() {
	
}

float UCorrectionContainer::ApplyCorrection (const float BaseValue) {
	
	float result = BaseValue;
	
	TArray<TScriptInterface<ICorrectionTypeInterface>> CorrectionTypes;
	
	for (auto Entry : CorrectionMap) {
		
		if (Entry == nullptr || Entry->CorrectionType)
		
		CorrectionTypes.Add(Entry->CorrectionType);
	}
	
	//優先度の高い順でソート
	CorrectionTypes.Sort([](const TScriptInterface<ICorrectionTypeInterface> A, const TScriptInterface<ICorrectionTypeInterface> B) {
		return A->GetPriority() < B->GetPriority();
	});
	
	if (CorrectionTypes.Num() == 0) {
		return result;
	}
	
	//優先度順に補正値を適用
	for (auto Type : CorrectionTypes) {
		
		TArray<TScriptInterface<ICorrectionValueInterface>> Values;
		TArray<UCorrectionMapEntry*> MatchEntries;
		
		///マップからタイプの合うエントリを取得
		for (auto Entry : CorrectionMap) {
			
			if (Entry == nullptr || Entry->CorrectionType == nullptr) {
				continue;
			}
			
			if (Entry->CorrectionType == Type) {
				MatchEntries.Add(Entry);
			}
		}
		///取得したエントリから補正値を取得
		for (auto Entry : MatchEntries) {
			Values.Append(Entry->CorrectionValues);
		}
		
		result = Type->ApplyCorrection(result, Values);
	}
	
	return result;
}

void UCorrectionContainer::AddCorrectionValue (const TScriptInterface<ICorrectionValueInterface> CorrectionValue) {
	
}

void UCorrectionContainer::RemoveCorrectionValue (const TScriptInterface<ICorrectionValueInterface> CorrectionValue) {
	
}

void UCorrectionContainer::ClearCorrectionValues () {
	
	CorrectionMap.Empty();
	
}
