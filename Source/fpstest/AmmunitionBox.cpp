// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmunitionBox.h"

// Sets default values
AAmmunitionBox::AAmmunitionBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

}

// Called when the game starts or when spawned
void AAmmunitionBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmmunitionBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

