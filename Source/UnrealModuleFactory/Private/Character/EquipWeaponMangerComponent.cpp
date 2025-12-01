// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EquipWeaponMangerComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InteractContext.h"
#include "Weapon/WeaponBase.h"
#include "Character/CharacterBase.h"

// Sets default values for this component's properties
UEquipWeaponMangerComponent::UEquipWeaponMangerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEquipWeaponMangerComponent::BeginPlay()
{
	Super::BeginPlay();

	InputAction = LoadObject<UInputAction>(NULL, TEXT("/UnrealModuleFactory/Input/IA_EquipWeapon.IA_EquipWeapon"), NULL, LOAD_None, NULL);
	// ...
	
	
	// 入力アクションの設定
	if (UEnhancedInputComponent* Component = CastChecked<UEnhancedInputComponent>(GetOwner()->InputComponent))
	{
		// 入力アクションのバインド
		Component->BindAction(InputAction, ETriggerEvent::Started, this, &UEquipWeaponMangerComponent::OnInputStarted);
		
		Component->BindAction(InputAction, ETriggerEvent::Canceled, this, &UEquipWeaponMangerComponent::OnInputCanceled);
		
		Component->BindAction(InputAction, ETriggerEvent::Triggered, this, &UEquipWeaponMangerComponent::OnInputTriggered);
	}
	
	if (const APlayerController* PlayerController = Cast<APlayerController>(Cast<ACharacterBase>(GetOwner())->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// 既存の入力マップの削除
			InputSystem->ClearAllMappings();

			// InputMapppingContextの設定
			int32 Priority = 0;
		}
	}
}


// Called every frame
void UEquipWeaponMangerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEquipWeaponMangerComponent::EquipWeapon(TSubclassOf<AWeaponBase> WeaponClass) {
	OnPreEquipWeapon(WeaponClass);
	
	ACharacterBase* OwnerCharacter = Cast<ACharacterBase>(GetOwner());
	
	AWeaponBase* WeaponActor = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass);
	
	EquippedWeapon = WeaponActor;
	
	if (WeaponActor && OwnerCharacter) {
		WeaponActor->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, EquipSocketName);
		WeaponActor->SetOwner(OwnerCharacter);
	}
	
	OnPostEquipWeapon();
}

void UEquipWeaponMangerComponent::OnPreEquipWeapon_Implementation(TSubclassOf<AWeaponBase> WeaponClass) {
	
}

void UEquipWeaponMangerComponent::OnPostEquipWeapon_Implementation() {
	
}

TArray<FString> UEquipWeaponMangerComponent::GetEquipSocketNames() const {
	TArray<FString> Options;
	Options.Add(TEXT("None"));
	// 1. このコンポーネントの持ち主（キャラクター）を取得
	const ACharacterBase* Character = Cast<ACharacterBase>(GetOwner());
	if (!Character) {
		return Options;
	}
	
	// 2. メッシュから全ソケット名を取得
	USkeletalMeshComponent* MeshComp = Character->GetMesh();
	if (MeshComp) {
		TArray<FName> SocketNames = MeshComp->GetAllSocketNames();
		for (const FName& Name : SocketNames) {
			Options.Add(Name.ToString());
		}
	}
	return Options;
}

void UEquipWeaponMangerComponent::OnInputStarted(const FInputActionValue& Value) {
	OnInputBase(ETriggerEvent::Started, Value, InteractText);
}

void UEquipWeaponMangerComponent::OnInputCanceled(const FInputActionValue& Value) {
	OnInputBase(ETriggerEvent::Canceled, Value, InteractText);
}

void UEquipWeaponMangerComponent::OnInputTriggered(const FInputActionValue& Value) {
	OnInputBase(ETriggerEvent::Triggered, Value, InteractText);
}

void UEquipWeaponMangerComponent::OnInputBase(const ETriggerEvent EventType, const FInputActionValue& Value, FText& OutputText) const {
	
	if (EquippedWeapon) {
		FInteractContext Context;
		Context.Interactor = GetOwner();
		Context.TriggerEvent = EventType;
		
		if (IInteractableInterface::Execute_Interactable(EquippedWeapon, Context, OutputText)) {
			IInteractableInterface::Execute_Interact(EquippedWeapon, Context);
		}
	}
}

