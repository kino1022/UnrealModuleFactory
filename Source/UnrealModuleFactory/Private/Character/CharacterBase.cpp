// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Character/CharacterBase.h"

#include "Action/AbilityInputAction.h"
#include "Action/ActionAbilitySystemComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/CharacterActionControlComponent.h"
#include "Public/UI/PlayerHUD.h"
#include "Character/HealthAttributeSet.h"
#include "Action/MoveActionAttributeSet.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACharacterBase::ACharacterBase() {
	
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthAttribute = CreateDefaultSubobject<UHealthAttributeSet>("HealthAttribute");
	
	MoveAttribute = CreateDefaultSubobject<UMoveActionAttributeSet>("MoveAttribute");
	
	AbilitySystemComponent = CreateDefaultSubobject<UActionAbilitySystemComponent>("AbilitySystemComponent");
	AddOwnedComponent(AbilitySystemComponent);
	
	ActionControl = CreateDefaultSubobject<UCharacterActionControlComponent>("ActionController");
	AddOwnedComponent(ActionControl);
	
	// キャラクターの回転とカメラの回転を分離する場合の設定
	// （キャラクターが向いている方向に勝手に回転しないようにする）
	/*
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;
	*/
    
	// 1. スプリングアームの作成
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent); // ルート（カプセル）に取り付ける// キャラクターからの距離（cm）
	CameraBoom->bUsePawnControlRotation = true; // コントローラー（マウス等）の回転にアームを追従させる
    
	// 2. カメラの作成
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // アームの先端に取り付ける
	FollowCamera->bUsePawnControlRotation = false; // カメラ自体は回転させず、アームの回転に任せる
    
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	// 回転の速度（滑らかさ）を設定
	// Pitch, Yaw, Roll の順。Yaw（Z軸回転）が旋回速度になります。
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	
	// おまけ：動きを少し滑らかにする（カメララグ）設定
	// これを有効にすると、プレイヤーが動いたときにカメラが少し遅れてついてくる演出になります
	CameraBoom->bEnableCameraLag = false;
	CameraBoom->CameraLagSpeed = 10.0f;
	
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay() {
	Super::BeginPlay();
	
	OnPreBegin();
	
	if (HUDWidget) {
		//HUDウィジェットの生成処理
		PlayerHUD = CreateWidget<UUserWidget>(GetWorld(), HUDWidget);
		if (PlayerHUD != nullptr) {
			PlayerHUD->AddToViewport();
			if (auto CastedHUD = Cast<UPlayerHUD>(PlayerHUD)) {
				CastedHUD->ChangeCharacter(this);
			}
		}
	}
	
	OnPostBegin();
	
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	
	if (EnhancedInputComponent && AbilityInputConfig && AbilitySystemComponent) {
		//　GASの入力登録処理
		for (const FAbilityInputAction& Action : AbilityInputConfig->AbilityInputActions) {
			if (Action.InputAction && Action.InputTag.IsValid()) {
				//入力開始時の登録処理
				EnhancedInputComponent->BindAction(
					Action.InputAction,
					ETriggerEvent::Started,
					this,
					&ACharacterBase::Input_AbilityInputTagPressed,
					Action.InputTag
					);
				//入力終了時の登録処理
				EnhancedInputComponent->BindAction(
					Action.InputAction,
					ETriggerEvent::Completed,
					this,
					&ACharacterBase::Input_AbilityInputTagReleased,
					Action.InputTag
					);
			}
		}
	}
}

void ACharacterBase::Input_AbilityInputTagPressed(FGameplayTag InputTag) {
	if (InputTag.IsValid() && AbilitySystemComponent) {
		AbilitySystemComponent->AbilityInputStarted(InputTag);
	}
}

void ACharacterBase::Input_AbilityInputTagReleased(FGameplayTag InputTag) {
	if (InputTag.IsValid() && AbilitySystemComponent) {
		AbilitySystemComponent->AbilityInputCanceled(InputTag);
	}
}
	

void ACharacterBase::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);
	if (NewController && AbilitySystemComponent) {
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		InitializeAttribute();
	}
}

void ACharacterBase::OnRep_PlayerState() {
	Super::OnRep_PlayerState();
	if (AbilitySystemComponent && GetPlayerState()) {
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void ACharacterBase::InitializeAttribute() {
	
}

