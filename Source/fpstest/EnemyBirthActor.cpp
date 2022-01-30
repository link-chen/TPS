// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBirthActor.h"

// Sets default values
AEnemyBirthActor::AEnemyBirthActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	time=0;

}

// Called when the game starts or when spawned
void AEnemyBirthActor::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(CountTimer,this,&AEnemyBirthActor::CreateSolider,1.0f,true,0);
}
void AEnemyBirthActor::CreateSolider()
{
	time++;
	if(time%CreateTime==0&&time)
	{
		UE_LOG(LogTemp,Warning,TEXT("Create"));
		GetWorld()->SpawnActor<AEnemySoldier>(EnemySoldierBluePrint,GetActorLocation(),GetActorRotation(),FActorSpawnParameters());
	}
}

// Called every frame
void AEnemyBirthActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

