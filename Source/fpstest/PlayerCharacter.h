// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "UMG.h"
#include "Bullte.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FPSTEST_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

    //摄像机和武器
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* Arm;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PlayerMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Gun1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Gun2;

	//攻击属性
	UPROPERTY(BlueprintReadWrite)
	int MaxBlood;
	UPROPERTY(BlueprintReadWrite)
	int CurrentBlood;
	UPROPERTY(BlueprintReadWrite)
	int HitValue;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="HUD")
	TSubclassOf<UUserWidget> HUDAssert;
	UPROPERTY()
	UUserWidget* HUDOverlay;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Gun");
	TSubclassOf<AGun> Gun;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//运动映射
	void MoveForward(float Value);
	void MoveRight(float Value);
	void StartJump();
	void StopJump();
	void RayCast();

	//
	UFUNCTION(BlueprintImplementableEvent)
	void Fire();
	UFUNCTION(BlueprintImplementableEvent)
	void Reload();
};
