// Fill out your copyright notice in the Description page of Project Settings.


#include "AK47.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AAK47::AAK47()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TotalBullteNumber=175;
	BullteNumber=35;
	TimeForNextShot=0.1;

	Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	Scene=CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Audio=CreateDefaultSubobject<UAudioComponent>(TEXT("FireSound"));
}

// Called when the game starts or when spawned
void AAK47::BeginPlay()
{
	Super::BeginPlay();
	
}
void AAK47::Fire()
{
	if(BullteNumber>0)
	{
		BullteNumber--;
		if(Audio!=nullptr)
		{
			Audio->Play();
			UE_LOG(LogTemp,Warning,TEXT("Fire"));
		}
	}
	else
	{
		//ReLoad();
	}
}
void AAK47::ReLoad()
{
	if(BullteNumber+TotalBullteNumber>35)
	{
		TotalBullteNumber+=BullteNumber;
		TotalBullteNumber-=35;
		BullteNumber=35;
	}
	else
	{
		BullteNumber+=TotalBullteNumber;
		TotalBullteNumber=0;
	}
}

// Called every frame
void AAK47::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

