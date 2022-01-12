// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	BullteNumber=35;
	TotalBullteNumber=175;
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AGun::Fire()
{
	if(BullteNumber>0)
	{
		BullteNumber--;
	}
	else
	{
		//ReLoad();
	}
}
void AGun::ReLoad()
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
