// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullte.h"
#include "AK47.generated.h"

UCLASS()
class FPSTEST_API AAK47 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAK47();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int BullteNumber;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int TotalBullteNumber;
	int MaxBullteNumber;
	int HitValue;
	UPROPERTY(EditAnywhere)
	float TimeForNextShot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* FireSpace;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Scene;
	UPROPERTY(EditAnywhere)
	UAudioComponent* Audio;

	UPROPERTY(EditAnywhere,Category="Bullte")
	TSubclassOf<class ABullte> Bullte;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Fire();
	UFUNCTION(BlueprintCallable)
	void ReLoad();
	UFUNCTION()
	void UseBullte();
	UFUNCTION(BlueprintImplementableEvent)
	void Light();

	FVector GetVector();
	FRotator GetFireRotator();
};
