// Fill out your copyright notice in the Description page of Project Settings.


#include "Grenade.h"

#include "EnemySoldier.h"

// Sets default values
AGrenade::AGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	HitPlace=CreateDefaultSubobject<UBoxComponent>(TEXT("BoomPlace"));

	FScriptDelegate OnOverLay;
	OnOverLay.BindUFunction(this,"OnOverLayBegin");
	HitPlace->OnComponentBeginOverlap.Add(OnOverLay);
}

// Called when the game starts or when spawned
void AGrenade::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(CountForBoom,this,&AGrenade::Count,1,true);
}
void AGrenade::Count()
{
	LeftTime--;
	if(!LeftTime)
	{
		Destroy();
	}
}
void AGrenade::OnOverlayBegin(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if(AEnemySoldier *Soldier=Cast<AEnemySoldier>(Other))
	{
		
	}
}

// Called every frame
void AGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

