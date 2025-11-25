#include "BulletCreator/Public/Movement/MovementStateMachine.h"

void UMovementStateMachine::OnPreTick(float DeltaTime) {
	
	Super::OnPreTick(DeltaTime);
	
	TTuple<bool, UMovementState*> TransitionResult = CheckTransitions();
	//ステート遷移が発生した場合、次のステートに変更する
	if (TransitionResult.Key && TransitionResult.Value != nullptr) {
		SetNextState(TransitionResult.Value);
	}
	
}

TTuple<bool, UMovementState*> UMovementStateMachine::CheckTransitions() {
	for (auto Entry : CurrentState->TransitionMap) {
		///遷移条件を満たしていた場合はtrueとセットのステートを変換
		if (Entry.Key->CheckTransition()) {
			if (Entry.Value == nullptr) {
				continue;
			}
			return TTuple<bool, UMovementState*>(true, Entry.Value);
		}
	}
	return TTuple<bool, UMovementState*>(false, nullptr);
}

bool UMovementStateMachine::SetNextState(UMovementState* NextState) {
	
	if (!NextState->SpeedLogic || !NextState->DirectionLogic) {
		return false;
	}
	
	if (!SetSpeedLogic(NextState->SpeedLogic)) return false;
	
	if (!SetDirectionLogic(NextState->DirectionLogic)) return false;
	
	return true;
}

void UMovementStateMachine::PreInitialize() {
	Super::PreInitialize();
	
	if (FirstState == nullptr) return;
	
	SetNextState(FirstState);
}
