// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMODULEFACTORY_API UUserHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable, Category="Player HUD")
	virtual bool SetCharacterModel (class ACharacterBase* CharacterModel);
	
	UFUNCTION(BlueprintNativeEvent, Category="Player HUD")
	void UpdateHealthBar();
	virtual void UpdateHealthBar_Implementation();
	
public:
	
	/* 参照している体力コンポーネント */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Player HUD")
	TWeakObjectPtr<class UHealthStatusComponent> HealthComponent;
	
	/* 参照している最大体力コンポーネント */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Player HUD")
	TWeakObjectPtr<class UMaxHealthComponent> MaxHealthComponent;
	
	/* 体力表示のプログレスバー */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Player HUD", meta = (BindWidget))
	class UProgressBar* HealthBar;
	
	/* 体力表示のテキスト */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Player HUD", meta = (BindWidget))
	class UTextBlock* TextView;
	
	/* 体力満タン時のバーの色 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Player HUD")
	FColor MaxColor;
	
	/* 体力ゼロ時のバーの色 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Player HUD")
	FColor MinColor;
	
	/* 体力変化の購読処理を行うメソッド */
	bool RegisterHealthDelegate();
	
	/* 最大体力変化の購読処理を行うメソッド */
	bool RegisterMaxHealthDelegate();
	
	/* 体力変化の購読の解除を行うメソッド */
	bool UnregisterHealthDelegate();
	
	/* 最大体力変化の購読の解除を行うメソッド */
	bool UnregisterMaxHealthDelegate();
};
