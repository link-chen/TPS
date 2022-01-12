// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "StartWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPSTEST_API UStartWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(Meta=(BindWidget))
		UButton* StartBtn;
	UPROPERTY(Meta=(BindWidget))
		UButton* QuitBtn;
	
public:
	virtual bool Initialize() override;

	UFUNCTION()
	void OnStartBtnClick();
	UFUNCTION()
	void OnQuitBtnClick();
};
