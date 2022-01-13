// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AK47.generated.h"

UCLASS()
class FPSTEST_API AAK47 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAK47();

	UPROPERTY(BlueprintReadWrite)
	int BullteNumber;
	UPROPERTY(BlueprintReadWrite)
	int TotalBullteNumber;
	int HitValue;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Scene;

	UPROPERTY(EditInstanceOnly,BlueprintReadWrite)
	FString GunLable;

	UPROPERTY(EditAnywhere)
	class USoundBase* Sound;
	
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
};
