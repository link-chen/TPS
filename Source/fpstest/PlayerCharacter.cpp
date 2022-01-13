// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "DrawDebugHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/GameSession.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//
	GetCapsuleComponent()->InitCapsuleSize(40,96);
	Camera=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Arm=CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Arm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation=true;
	Gun1=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh1"));
	Gun1->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,"weapon");
	Gun2=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh2"));
	Gun2->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,"weapon");
	//
	MaxBlood=100;
	CurrentBlood=MaxBlood;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(HUDAssert!=nullptr)
	{
		HUDOverlay=CreateWidget<UUserWidget>(GetWorld(),HUDAssert);
		if(HUDOverlay!=nullptr)
		{
			HUDOverlay->AddToViewport();
		}
	}
	if(Gun!=nullptr)
	{
		AK=GetWorld()->SpawnActor<AAK47>(Gun,GetActorLocation(),GetActorRotation(),FActorSpawnParameters());
		AK->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepWorldTransform,"weapon");
	}
}
// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RayCast();
}
void APlayerCharacter::MoveForward(float Value)
{
	FVector Direct=FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direct,Value);
}
void APlayerCharacter::MoveRight(float Value)
{
	FVector Direct=FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direct,Value);
}
void APlayerCharacter::StartJump()
{
	bPressedJump=true;
}
void APlayerCharacter::StopJump()
{
	bPressedJump=false;
}
void APlayerCharacter::RayCast()
{
	FVector Start=Camera->GetComponentLocation();
	FVector End=Camera->GetComponentLocation()+Camera->GetForwardVector()*1000;
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult,Start,End,ECollisionChannel::ECC_Visibility,NULL);
}
void APlayerCharacter::Fire()
{
	if(AK!=nullptr)
		AK->Fire();
}
void APlayerCharacter::Reload()
{
	if(AK!=nullptr)
		AK->ReLoad();
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn",this,&APlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&APlayerCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&APlayerCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&APlayerCharacter::StopJump);

	PlayerInputComponent->BindAction("Fire",IE_Pressed,this,&APlayerCharacter::Fire);
	PlayerInputComponent->BindAction("Reload",IE_Pressed,this,&APlayerCharacter::Reload);
}

