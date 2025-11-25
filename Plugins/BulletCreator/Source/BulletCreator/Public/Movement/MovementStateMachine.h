#pragma once
#include "MovementState.h"
#include "Movement/BulletMovementController.h"
#include "MovementStateMachine.generated.h"

UCLASS( ClassGroup=(BulletMovement), meta=(BlueprintSpawnableComponent) , Blueprintable)
class UMovementStateMachine : public UBulletMovementController {
	
	GENERATED_BODY()
	
public:
	
	UMovementStateMachine(){}
	
	///ステートが遷移するかどうかを判定し、遷移する場合は次のステートを返す
	virtual TTuple<bool, UMovementState*> CheckTransitions();
	
	///ステートを変化させる
	UFUNCTION(BlueprintCallable, Category = "Movement State Machine")
	virtual bool SetNextState (UMovementState* NextState);
	
	virtual void OnPreTick(float DeltaTime) override;
	
	virtual void PreInitialize() override;
	
protected:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement State Machine")
	UMovementState* FirstState;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Movement State Machine")
	UMovementState* CurrentState;
};
