// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/WeaponBase.h"

#include "InteractContext.h"
#include "Public/Weapon/Interface/InteractConditionInterface.h"
#include "Public/Weapon/Interface/InteractBehaviourInterface.h"
#include "UObject/Interface.h"
#include "Weapon/WeaponModuleComponent.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = Cast<USceneComponent>(WeaponMesh);
	
	OnInputInteract = false;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay() {
	
	Super::BeginPlay();
	
	TArray<UActorComponent*> Components;
	GetComponents(Components);
	for (UActorComponent* Component : Components) {
		if (UWeaponModuleComponent* Module = Cast<UWeaponModuleComponent>(Component)) {
			ModuleComponents.Add(Module);
		}
	}
	
	CachedConditions = GetInteractConditions();
	
	CachedBehaviours = GetInteractBehaviours();
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

bool AWeaponBase::Interactable_Implementation(FInteractContext& Context, FText& InteractionOutput) {
	return GetInteractableCondition(Context, InteractionOutput);
}

void AWeaponBase::Interact_Implementation(const FInteractContext& Context) {
	SortBehaviourList(CachedBehaviours);
	switch (Context.TriggerEvent) {
		case ETriggerEvent::Started:
			/*
			for (const TScriptInterface<IInteractBehaviourInterface> Behaviour : CachedBehaviours) {
				IInteractBehaviourInterface::Execute_StartInteract(Behaviour.GetObject(), const_cast<FInteractContext&>(Context));
			}
			*/
			break;
		case ETriggerEvent::Triggered:
			/*
			const float DeltaTime = GetWorld()->GetDeltaSeconds();
			for (const TScriptInterface<IInteractBehaviourInterface> Behaviour : CachedBehaviours) {
				IInteractBehaviourInterface::Execute_TickInteract(Behaviour.GetObject(), DeltaTime, const_cast<FInteractContext&>(Context));
			}
			*/
			break;
		case ETriggerEvent::Canceled:
			/*
			for (const TScriptInterface<IInteractBehaviourInterface> Behaviour : CachedBehaviours) {
				IInteractBehaviourInterface::Execute_CancelInteract(Behaviour.GetObject(), const_cast<FInteractContext&>(Context));
			}
			*/
			break;
		default:
			break;
	}
}

bool AWeaponBase::GetInteractableCondition (FInteractContext& Context, FText& InteractText)  {
	SortConditionList(CachedConditions);
	for (const TScriptInterface<IInteractConditionInterface> Condition : CachedConditions) {
		if (!IInteractConditionInterface::Execute_Interactable(Condition.GetObject(), Context, InteractText)) {
			return false;
		}
	}
	return true;
}

TArray<TScriptInterface<IInteractConditionInterface>> AWeaponBase::GetInteractConditions() const {
    
    if (ModuleComponents.Num() == 0) {
        return TArray<TScriptInterface<IInteractConditionInterface>>();
    }
    
    TArray<TScriptInterface<IInteractConditionInterface>> Results;
    
    for (UWeaponModuleComponent* Module : ModuleComponents) {
        
        if (!Module) {
            continue;
        }
        
        // 修正: Condition インターフェースをチェック
        if (Module->GetClass()->ImplementsInterface(UInteractConditionInterface::StaticClass())) {
            Results.Add(Module);
        }
    }
    
    return Results;
}

TArray<TScriptInterface<IInteractBehaviourInterface>> AWeaponBase::GetInteractBehaviours() const {
    
    if (ModuleComponents.Num() == 0) {
        return TArray<TScriptInterface<IInteractBehaviourInterface>>();
    }
    
    TArray<TScriptInterface<IInteractBehaviourInterface>> Results;
    
    for (UWeaponModuleComponent* Module : ModuleComponents) {
        
        if (!Module) {
            continue;
        }
        
        // 修正: Behaviour インターフェースをチェック
        if (Module->GetClass()->ImplementsInterface(UInteractBehaviourInterface::StaticClass())) {
            Results.Add(Module);
        }
    }
    
    return Results;
}

void AWeaponBase::SortConditionList(TArray<TScriptInterface<IInteractConditionInterface>>& Array) const {
    Array.Sort([](const TScriptInterface<IInteractConditionInterface>& A, const TScriptInterface<IInteractConditionInterface>& B) {
        return IInteractConditionInterface::Execute_GetConditionPriority(A.GetObject()) < IInteractConditionInterface::Execute_GetConditionPriority(B.GetObject());
    });
}

void AWeaponBase::SortBehaviourList(TArray<TScriptInterface<IInteractBehaviourInterface>>& Array) const {
    Array.Sort([](const TScriptInterface<IInteractBehaviourInterface>& A, const TScriptInterface<IInteractBehaviourInterface>& B) {
        return IInteractBehaviourInterface::Execute_GetBehaviourPriority(A.GetObject()) < IInteractBehaviourInterface::Execute_GetBehaviourPriority(B.GetObject());
    });
}
