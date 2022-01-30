// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemySoldier.generated.h"

UCLASS()
class FPSTEST_API AEnemySoldier : public ACharacter
{
	GENERATED_BODY()

public:
	FTimerHandle TimerHandle_Count;
	UPROPERTY(EditAnywhere)
	int LiveTime=30;
	int MaxBlood;
	int CurrentBlood;
	// Sets default values for this character's properties
	AEnemySoldier();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void Count();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
