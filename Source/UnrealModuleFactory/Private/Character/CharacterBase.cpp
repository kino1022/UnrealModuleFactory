// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Character/CharacterBase.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Public/UI/PlayerHUD.h"

// Sets default values
ACharacterBase::ACharacterBase() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = CreateDefaultSubobject<UHealthStatusComponent>("Health");
	AddOwnedComponent(Health);
	
	MaxHealth = CreateDefaultSubobject<UMaxHealthComponent>("MaxHealth");
	AddOwnedComponent(MaxHealth);
	
	
	// キャラクターの回転とカメラの回転を分離する場合の設定
	// （キャラクターが向いている方向に勝手に回転しないようにする）
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
    
	// 1. スプリングアームの作成
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent); // ルート（カプセル）に取り付ける// キャラクターからの距離（cm）
	CameraBoom->bUsePawnControlRotation = true; // コントローラー（マウス等）の回転にアームを追従させる
    
	// 2. カメラの作成
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // アームの先端に取り付ける
	FollowCamera->bUsePawnControlRotation = false; // カメラ自体は回転させず、アームの回転に任せる
    
	// おまけ：動きを少し滑らかにする（カメララグ）設定
	// これを有効にすると、プレイヤーが動いたときにカメラが少し遅れてついてくる演出になります
	CameraBoom->bEnableCameraLag = false;
	CameraBoom->CameraLagSpeed = 10.0f;
	
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay() {
	
	Super::BeginPlay();
	
	//最大体力ステータスの初期化処理
	if (MaxHealth != nullptr) {
		IStatusInterface::Execute_SetStatusValue(MaxHealth, InitData.MaxHealth);
	}
	
	//体力ステータスの初期化処理
	if (Health != nullptr) {
		IStatusInterface::Execute_SetStatusValue(Health, InitData.InitialHealth);
	}
	
	
	PlayerHUD = CreateWidget<UUserWidget>(GetWorld(), HUDWidget);
	if (PlayerHUD != nullptr) {
		PlayerHUD->AddToViewport();
		if (auto CastedHUD = Cast<UPlayerHUD>(PlayerHUD)) {
			CastedHUD->ChangeCharacter(this);
		}
	}
	
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

