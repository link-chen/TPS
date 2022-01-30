// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemySoldier.h"
#include "GameFramework/Actor.h"
#include "EnemyBirthActor.generated.h"

UCLASS()
class FPSTEST_API AEnemyBirthActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyBirthActor();

	FTimerHandle CountTimer;
	int time;

	UPROPERTY(EditAnywhere)
	int CreateTime;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemySoldier>	EnemySoldierBluePrint;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void CreateSolider();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
