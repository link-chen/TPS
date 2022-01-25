// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullte.h"

#include "EnemySoldier.h"

// Sets default values
ABullte::ABullte()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	CollisonComponent=CreateDefaultSubobject<USphereComponent>(TEXT("Collison"));
	CollisonComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisonComponent->SetSphereRadius(15.0);
	Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CollisonComponent);
	
	FScriptDelegate Hit;
	Hit.BindUFunction(this,"OnOverlayBegin");
	CollisonComponent->OnComponentBeginOverlap.Add(Hit);
	Mesh->OnComponentBeginOverlap.Add(Hit);
	

	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MoveComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisonComponent);
	ProjectileMovementComponent->InitialSpeed=300;
	ProjectileMovementComponent->MaxSpeed=300;
	
	InitialLifeSpan = 9.0f;
}

// Called when the game starts or when spawned
void ABullte::BeginPlay()
{
	Super::BeginPlay();
}
void ABullte::OnOverlayBegin(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if(AEnemySoldier* Soldier=Cast<AEnemySoldier>(Other))
	{
		Soldier->CurrentBlood-=45;
	}
}
// Called every frame
void ABullte::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

