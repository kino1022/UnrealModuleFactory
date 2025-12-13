// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Movement/MovementControlComponent.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Collision/BulletCollisionControlComponent.h"
#include "Collision/BulletHitContext.h"
#include "Range/BulletRangeRecorder.h"

// Sets default values
ABulletActor::ABulletActor() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletSphere = CreateDefaultSubobject<USphereComponent>(FName("SphereComponent"));
	RootComponent = BulletSphere;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	AddOwnedComponent(BulletMesh);

	BulletCollision = CreateDefaultSubobject<UBulletCollisionControlComponent>(TEXT("BulletCollision"));
	AddOwnedComponent(BulletCollision);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	AddOwnedComponent(ProjectileMovement);
	
	MovementControl = CreateDefaultSubobject<UMovementControlComponent>(TEXT("MovementControl"));
	AddOwnedComponent(MovementControl);
	
	RangeRecorder = CreateDefaultSubobject<UBulletRangeRecorder>(TEXT("RangeRecorder"));
	AddOwnedComponent(RangeRecorder);
	
	//Sphereコンポーネント本位での物理挙動を有効に
	BulletSphere->SetSimulatePhysics(true);
	//衝突時のコールバックを登録
	BulletSphere->OnComponentHit.AddDynamic(this, &ABulletActor::OnHit);
	
	//Mesh本位での物理挙動を無効に
	BulletMesh->SetSimulatePhysics(false);
}

void ABulletActor::SetOwnerCharacter(class ACharacter* NewOwnerCharacter) {
	if (!NewOwnerCharacter) {
		return;
	}
	OwnerCharacter = NewOwnerCharacter;
}

ACharacter* ABulletActor::GetOwnerCharacter() const {
	if (!OwnerCharacter.IsValid()) {
		return nullptr;
	}
	return OwnerCharacter.Get();
}

UMeshComponent* ABulletActor::GetBulletMesh () const {
	return BulletMesh;
}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void ABulletActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ABulletActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	FBulletHitContext HitContext;
	HitContext.Hit = Hit;
	HitContext.NormalImpulse = NormalImpulse;
	HitContext.OtherActor = OtherActor;
	HitContext.OtherComp = OtherComp;
	HitContext.BulletActor = this;
	if (BulletCollision) {
		BulletCollision->OnHit(HitContext);
	}
}
