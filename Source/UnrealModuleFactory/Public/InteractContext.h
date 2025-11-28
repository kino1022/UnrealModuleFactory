#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "InputAction.h" // <-- 追加: ETriggerEvent を定義するヘッダ
#include "InteractContext.generated.h"

UENUM(Blueprintable, BlueprintType)
enum class EInteractType : uint8 {
	Primary,
	Secondary,
};

/**
 * UInteractableInterfaceで使用されるコンテキスト情報を格納する構造体
 */
USTRUCT(BlueprintType)
struct FInteractContext {
	
	GENERATED_BODY();
	
public:
	
	/*
	 *オブジェクトを使用するクラス
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Interact Context")
	AActor* Interactor;

	/*
	 *使用の種類
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Interact Context")
	EInteractType InteractType;
	
	/*
	 * 使用入力の値
	 */
	FInputActionValue InputValue;
	
	/*
	 * 
	 */
	ETriggerEvent TriggerEvent;
	
	/*
	 *現在インタラクトされているかどうか
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Interact Context")
	bool OnInteract;
	
};
