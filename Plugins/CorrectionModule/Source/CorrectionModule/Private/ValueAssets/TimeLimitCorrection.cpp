#include "CorrectionModule/Public/ValueAssets/TimeLimitCorrection.h"


void UTimeLimitCorrection::StartTimer() {
	
	UE_LOG(LogTemp, Log, TEXT("StartTimer()"));
	
	auto World = GetWorld();
	
	if (World) {
		World->GetTimerManager().SetTimer(
			TimerHandle,
			this,
			&UTimeLimitCorrection::OnCountZero,
			Duration,
			false
			);
	}
	
}

void UTimeLimitCorrection::OnCountZero() {
	EnableCorrection = false;
}


