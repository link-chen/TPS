// Fill out your copyright notice in the Description page of Project Settings.


#include "Grenade.h"

#include "EnemySoldier.h"
#include "PlayerCharacter.h"

// Sets default values
AGrenade::AGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	HitPlace=CreateDefaultSubobject<UBoxComponent>(TEXT("BoomPlace"));
	HitPlace->SetupAttachment(Mesh);
	bBoom=false;
	
	FScriptDelegate OnOverLay;
	OnOverLay.BindUFunction(this,"OnOverlayBegin");
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
		bBoom=true;
	}
}
void AGrenade::OnOverlayBegin(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if(bBoom)
	{
		if(AEnemySoldier *Soldier=Cast<AEnemySoldier>(Other))
		{
			Soldier->CurrentBlood-=1000;
		}
		if(APlayerCharacter* Player=Cast<APlayerCharacter>(Other))
		{
			Player->CurrentBlood-=75;
		}
	}
}

// Called every frame
void AGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

