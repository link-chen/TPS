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
		AK->SetActorRotation(FRotator(90.0f,-90.0f,-0.0f));
		AK->AddActorLocalRotation(FRotator(-41.5f,0.0f,0.0f));
		AK->SetActorLocation(FVector(3.563325f,-1.409857f,4.817779f));
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
	// 获取摄像机变换。
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	// 设置MuzzleOffset，在略靠近摄像机前生成发射物。
	MuzzleOffset.Set(0.0f, 45.0f, 5.0f);

	// 将MuzzleOffset从摄像机空间变换到世界空间。
	FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

	// 使目标方向略向上倾斜。
	FRotator MuzzleRotation = CameraRotation;
	if(AK!=nullptr)
		AK->Fire(MuzzleLocation,MuzzleRotation);
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
	PlayerInputComponent->BindAxis("LookUp",this,&APlayerCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&APlayerCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&APlayerCharacter::StopJump);
	PlayerInputComponent->BindAction("Fire",IE_Pressed,this,&APlayerCharacter::Fire);
	PlayerInputComponent->BindAction("Fire",IE_Released,this,&APlayerCharacter::CancleFire);
	PlayerInputComponent->BindAction("Reload",IE_Pressed,this,&APlayerCharacter::Reload);
	PlayerInputComponent->BindAction("ShowBag",IE_Pressed,this,&APlayerCharacter::ShowBag);
	PlayerInputComponent->BindAction("Aim",IE_Pressed,this,&APlayerCharacter::Fun);
}

