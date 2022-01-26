// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySoldier.h"

// Sets default values
AEnemySoldier::AEnemySoldier()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MaxBlood=150;
	CurrentBlood=MaxBlood;
}

// Called when the game starts or when spawned
void AEnemySoldier::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_Count,this,&AEnemySoldier::Count,1,true);
}

// Called every frame
void AEnemySoldier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(CurrentBlood<=0)
	{
		Destroy();
	}

}
void AEnemySoldier::Count()
{
	if(LiveTime)
	{
		LiveTime--;
	}
	else
	{
		Destroy();
	}
}

// Called to bind functionality to input
void AEnemySoldier::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

