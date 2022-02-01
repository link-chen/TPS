// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "UMG.h"
#include "AK47.h"
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
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* Arm;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PlayerMesh;
	
	// 枪口相对于摄像机位置的偏移。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;
	
	//玩家基础属性
	UPROPERTY(BlueprintReadWrite)
	int MaxBlood;
	UPROPERTY(BlueprintReadWrite)
	int CurrentBlood;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int PlayerHitValue=5;
	UPROPERTY(BlueprintReadWrite)
	bool bCanLoadBullte;
	UPROPERTY(BlueprintReadWrite)
	int Level;
	UPROPERTY()
	int UPGradeExpress;
	UPROPERTY(BlueprintReadWrite)
	int CurrentExpress;
	
	//行动模式属性
	UPROPERTY(EditAnywhere)
	float WalkSpeed;
	UPROPERTY(EditAnywhere)
	float RunSpeed;

	//枪械属性界面和玩家生命值界面
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="HUD")
	TSubclassOf<UUserWidget> HUDAssert;
	UPROPERTY()
	UUserWidget* HUDOverlay;

	//泛型枪械
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Gun")
	TSubclassOf<class AAK47> Gun0;
	UPROPERTY(BlueprintReadWrite)
	AAK47* AK0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Gun")
	TSubclassOf<class AAK47> Gun1;
	UPROPERTY(BlueprintReadWrite)
	AAK47* AK1;
	UPROPERTY()
	AAK47* ChangeGun;

	//动画
	UPROPERTY(EditAnywhere)
	UAnimMontage* ReLoadAnimMontage;
	UPROPERTY(EditAnywhere)
    UAnimMontage* FireAnimMontage;

	//连发计时器
	FTimerHandle ShotTime;
	
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

	//枪械功能
	UFUNCTION()
	void Fire();
	UFUNCTION()
	void Reload();
	UFUNCTION()
	void GunFire();
	UFUNCTION()
	void CancleFire();
	UFUNCTION()
	void ReLoadBullte();
	
	//背包设置
	void ShowBag();
	UFUNCTION()
	
	void Fun();

	UFUNCTION(BlueprintCallable)
	void CheckUpGrade();
	void UpGrade();

	//换抢
	UFUNCTION()
	void ChangeGunF();

	//行动模式
	UFUNCTION()
	void TurnIntoActiveMode();
	UFUNCTION()
	void CancleActiveMode();
};