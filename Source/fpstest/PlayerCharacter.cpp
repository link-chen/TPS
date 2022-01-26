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
	
	//设置胶囊体/弹簧臂/摄像机
	GetCapsuleComponent()->InitCapsuleSize(40,96);
	Camera=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Arm=CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Arm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(RootComponent);

	//生命值相关设计
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
		AK->SetActorRelativeRotation(FRotator(0.238f,-87.199f,0.092f));
		AK->SetActorLocation(FVector(3.90425f,-1.532887f,0.834234f));
		AK->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,"WeaponSocket");
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
	GunFire();
	GetWorldTimerManager().SetTimer(ShotTime,this,&APlayerCharacter::GunFire,AK->TimeForNextShot,true);
}
void APlayerCharacter::CancleFire()
{
	GetWorldTimerManager().ClearTimer(ShotTime);
}

void APlayerCharacter::Reload()
{
	if(AK!=nullptr)
		AK->ReLoad();
}
void APlayerCharacter::GunFire()
{
	if(AK!=nullptr)
	{
		AK->Fire();
	}
}
void APlayerCharacter::ShowBag()
{
	
}
void APlayerCharacter::Fun()
{
	
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn",this,&APlayerCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&APlayerCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&APlayerCharacter::StopJump);
	PlayerInputComponent->BindAction("Fire",IE_Pressed,this,&APlayerCharacter::Fire);
	PlayerInputComponent->BindAction("Fire",IE_Released,this,&APlayerCharacter::CancleFire);
	PlayerInputComponent->BindAction("Reload",IE_Pressed,this,&APlayerCharacter::Reload);
	PlayerInputComponent->BindAction("ShowBag",IE_Pressed,this,&APlayerCharacter::ShowBag);
	PlayerInputComponent->BindAction("Aim",IE_Pressed,this,&APlayerCharacter::Fun);
}

