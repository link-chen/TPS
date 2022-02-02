// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmunitionBox.h"
#include "PlayerCharacter.h"

// Sets default values
AAmmunitionBox::AAmmunitionBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Box=CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(Mesh);
	FScriptDelegate OverLayBegin;
	OverLayBegin.BindUFunction(this,"OnOverlayBegin");
	FScriptDelegate OverLayEnd;
	OverLayEnd.BindUFunction(this,"OnOverLayEnd");
	Box->OnComponentBeginOverlap.Add(OverLayBegin);
	Box->OnComponentEndOverlap.Add(OverLayEnd);
}

// Called when the game starts or when spawned
void AAmmunitionBox::BeginPlay()
{
	Super::BeginPlay();
	
}
void AAmmunitionBox::OnOverlayBegin(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if(APlayerCharacter* Player=Cast<APlayerCharacter>(Other))
	{
		Player->bCanLoadBullte=true;
	}
}
void AAmmunitionBox::OnOverlayEnd(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if(APlayerCharacter* Player=Cast<APlayerCharacter>(Other))
	{
		Player->bCanLoadBullte=false;
	}
}

// Called every frame
void AAmmunitionBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

