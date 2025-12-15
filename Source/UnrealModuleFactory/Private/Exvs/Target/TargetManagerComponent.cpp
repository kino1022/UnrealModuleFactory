#include "Exvs/Target/TargetManagerComponent.h"
#include "Exvs/ExvsCharacterBase.h"

UTargetManagerComponent::UTargetManagerComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTargetManagerComponent::BeginPlay() {
	Super::BeginPlay();
}

FLockTargetContext& UTargetManagerComponent::GetTargetContext() {
	return LockTargetContext;
}

void UTargetManagerComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateTargetContext();
}

void UTargetManagerComponent::SwitchLockTarget_Implementation(const struct FInputActionValue& Value) {
	//ターゲットの切り替えロジックをここに実装
	//どうやって出ているターゲット候補を取得するかは考えておく
}

void UTargetManagerComponent::UpdateTargetContext_Implementation() {
	if (!LockTargetActor.IsValid()) {
		LockTargetContext.bHasLockTarget = false;
		LockTargetContext.LockTargetActor = nullptr;
		LockTargetContext.LockTargetDistance = 0.0f;
		return;
	}
	
	AExvsCharacterBase* TargetActor = LockTargetActor.Get();
	if (!TargetActor) {
		LockTargetContext.bHasLockTarget = false;
		LockTargetContext.LockTargetActor = nullptr;
		LockTargetContext.LockTargetDistance = 0.0f;
		return;
	}
	
	LockTargetContext.bHasLockTarget = true;
	LockTargetContext.LockTargetActor = LockTargetActor;
	
	if (AActor* OwnerActor = GetOwner()) {
		LockTargetContext.LockTargetDistance = FVector::Distance(OwnerActor->GetActorLocation(), LockTargetActor->GetActorLocation());
	}
}
