// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullte.h"

#include "EnemySoldier.h"

// Sets default values
ABullte::ABullte()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	FScriptDelegate Hit;
	Hit.BindUFunction(this,"OnHit");
	Mesh->OnComponentHit.Add(Hit);

	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MoveComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(Mesh);
	ProjectileMovementComponent->InitialSpeed=300;
	ProjectileMovementComponent->MaxSpeed=300;
	
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void ABullte::BeginPlay()
{
	Super::BeginPlay();
}
void ABullte::OnHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if(AEnemySoldier* Soldier=Cast<AEnemySoldier>(Other))
	{
		Soldier->CurrentBlood-=45;
		Destroy();
	}
}
// Called every frame
void ABullte::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

