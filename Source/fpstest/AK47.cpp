// Fill out your copyright notice in the Description page of Project Settings.


#include "AK47.h"

#include "MovieSceneTracksComponentTypes.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAK47::AAK47()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TimeForNextShot=0.1;
	
	Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	Scene=CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FireSpace=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FireSpace"));
	FireSpace->AttachToComponent(Mesh,FAttachmentTransformRules::KeepRelativeTransform,"Muzzle");
	Audio=CreateDefaultSubobject<UAudioComponent>(TEXT("FireSound"));
}

// Called when the game starts or when spawned
void AAK47::BeginPlay()
{
	Super::BeginPlay();
	
	MaxBullteNumber=BullteNumber;
}
void AAK47::Fire()
{
	if(BullteNumber>0)
	{
		BullteNumber--;
		Light();
		UseBullte();
		if(Audio!=nullptr)
		{
			Audio->Play();
		}
	}
	else
	{
		//ReLoad();
	}
}
void AAK47::UseBullte()
{
	if(Bullte)
	{
		UWorld* World=GetWorld();
		if(World)
		{
			UE_LOG(LogTemp,Warning,TEXT("Fire"));
			ABullte* GunBullte=World->SpawnActor<ABullte>(Bullte,GetVector(),GetFireRotator()+FRotator(0.0f,90.0f,0.0f));
		}
	}
}

void AAK47::ReLoad()
{
	if(BullteNumber+TotalBullteNumber>MaxBullteNumber)
	{
		TotalBullteNumber+=BullteNumber;
		TotalBullteNumber-=MaxBullteNumber;
		BullteNumber=MaxBullteNumber;
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
FVector AAK47::GetVector()
{
	return FireSpace->GetComponentLocation();
}

FRotator AAK47::GetFireRotator()
{
	return FireSpace->GetComponentRotation();
}

