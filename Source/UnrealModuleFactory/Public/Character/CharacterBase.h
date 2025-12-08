// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Action/ActionAbilitySystemComponent.h"
#include "Action/AbilityInputConfig.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CharacterBase.generated.h"

UCLASS()
class UNREALMODULEFACTORY_API ACharacterBase : public ACharacter, public IAbilitySystemInterface {
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();
	
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override {
		return Cast<UAbilitySystemComponent>(AbilitySystemComponent);
	}
	
	UFUNCTION(BlueprintNativeEvent, Category = "Character")
	void OnPreBegin ();
	virtual void OnPreBegin_Implementation() {}
	
	UFUNCTION(BlueprintNativeEvent, Category = "Character")
	void OnPostBegin();
	virtual void OnPostBegin_Implementation() {}

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	/* 体力のアトリビュート */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CharacterBase")
	class UHealthAttributeSet* HealthAttribute;
	
	/* 移動速度のアトリビュート */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CharacterBase")
	class UMoveActionAttributeSet* MoveAttribute;
	
	/* 自撮り棒 */
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category="CharacterBase")
	class USpringArmComponent* CameraBoom;
	
	/* 追従メインカメラ */
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category="CharacterBase")
	class UCameraComponent* FollowCamera;
	
	/* アビリティ管理を行うカスタムコンポーネント */
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category="CharacterBase")
	class UActionAbilitySystemComponent* AbilitySystemComponent;
	
	/* アビリティと入力の紐付けデータ */
	UPROPERTY(EditDefaultsOnly, Category="CharacterBase")
	TObjectPtr<UAbilityInputConfig> AbilityInputConfig;
	
	/* 通常アクションの入力マップ */
	UPROPERTY(EditDefaultsOnly, Category="CharacterBase|Input")
	class UInputMappingContext* DefaultMapping;
	
	/* 通常アクションの制御コンポーネント */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CharacterBase")
	class UCharacterActionControlComponent* ActionControl;
	
	/* 画面上に配置するHUDのクラス */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CharacterBase")
	TSubclassOf<class UUserWidget> HUDWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CharacterBase")
	UUserWidget* PlayerHUD;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void Input_AbilityInputTagPressed(FGameplayTag InputTag);
	
	void Input_AbilityInputTagReleased(FGameplayTag InputTag);
	
protected:
	
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void OnRep_PlayerState() override;
	
	/* 各種AttributeSetの初期化処理を行うメソッド */
	virtual void InitializeAttribute ();
	
};
