// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Shoot/ShootBulletModuleComponent.h"
#include "InteractContext.h"
#include "../../../../Plugins/BulletCreator/Source/BulletCreator/Public/Bullet.h"
#include "Weapon/FireControl/FireControlLogic.h"
#include "Weapon/WeaponBase.h"
#include "Weapon/Spawn/ShootSpawnLogic.h"

UShootBulletModuleComponent::UShootBulletModuleComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UShootBulletModuleComponent::BeginPlay() {
	Super::BeginPlay();
	
	if (FireControlLogic) {
		FireControlLogic->BindFireDelegate(FOnFireDelegate::FDelegate::CreateUObject(this, &UShootBulletModuleComponent::OnFire));
	}
}

void UShootBulletModuleComponent::StartInteract_Implementation(FInteractContext& Context) {
	if (FireControlLogic) {
		FireControlLogic->OnStartFire();
	}
}

void UShootBulletModuleComponent::CancelInteract_Implementation(FInteractContext& Context) {
	if (FireControlLogic) {
		FireControlLogic->OnStopFire();
	}
}

void UShootBulletModuleComponent::TickInteract_Implementation(float DeltaTime, FInteractContext& Context) {
	if (FireControlLogic) {
		FireControlLogic->OnTickFire(DeltaTime);
	}
}

void UShootBulletModuleComponent::SetBehaviourPriority_Implementation(int NewPriority) {
	BehaviourPriority = NewPriority;
}

TArray<FString> UShootBulletModuleComponent::GetSocketNameOptions() const {
    
    TArray<FString> Options;
    Options.Add(TEXT("None"));
    // 1. このモジュールの持ち主（武器）を取得
    // ランタイムでは GetOwner() を優先し、エディタ編集時（CDOなど）で得られない場合は GetOuter() をフォールバックする
    const AWeaponBase* Weapon = Cast<AWeaponBase>(GetOwner());
    if (!Weapon) {
        Weapon = Cast<AWeaponBase>(GetOuter());
    }
    
    if (Weapon && Weapon->GetWeaponMesh()) {
        
        // 2. メッシュから全ソケット名を取得
        TArray<FName> SocketNames = Weapon->GetWeaponMesh()->GetAllSocketNames();
        for (const FName& Name : SocketNames)
        {
            Options.Add(Name.ToString());
        }
        
    }
    
    return Options;
}

void UShootBulletModuleComponent::OnFire(FName SocketName) {
	if (ShootSpawnLogic) {
		ShootSpawnLogic->OnBulletSpawn(BulletActor, SocketName);
	}
}
