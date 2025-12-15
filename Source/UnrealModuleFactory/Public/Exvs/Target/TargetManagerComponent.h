#pragma once

#include "Components/ActorComponent.h"
#include "TargetManagerComponent.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FLockTargetContext {
	
	GENERATED_BODY()
	
public:
	
	/** ロックしているターゲットが存在するか */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bHasLockTarget;
	
	/** ロックしている対象のキャラクター */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<class AExvsCharacterBase> LockTargetActor;
	
	/** ロックしている対象との距離 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float LockTargetDistance;
};

UCLASS()
class UTargetManagerComponent : public UActorComponent {
	
	GENERATED_BODY()
	
public:

	UTargetManagerComponent();
	
	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	/** 現在ロックしているターゲットキャラクターを取得 */
	UFUNCTION(BlueprintCallable, Category = "Exvs|Target")
	FLockTargetContext& GetTargetContext ();
	
	/** ターゲット切り替え入力処理 */
	UFUNCTION(BlueprintNativeEvent, Category = "Exvs|Target")
	void SwitchLockTarget (const struct FInputActionValue& Value);
	virtual void SwitchLockTarget_Implementation (const struct FInputActionValue& Value);
	
	/** ターゲットコンテキスト更新処理 */
	UFUNCTION(BlueprintNativeEvent, Category = "Exvs|Target")
	void UpdateTargetContext ();
	virtual void UpdateTargetContext_Implementation ();
	
protected:
	
	/** 現在ロックしているターゲットキャラクター */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Exvs|Target", meta = (AllowPrivateAccess = true))
	TWeakObjectPtr<class AExvsCharacterBase> LockTargetActor;
	
	/** ターゲット切り替え用の入力アクション */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Exvs|Target", meta = (AllowPrivateAccess = true))
	TObjectPtr<class UInputAction> SwitchTargetInput;
	
	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = "Exvs|Target")
	FLockTargetContext LockTargetContext;
};
