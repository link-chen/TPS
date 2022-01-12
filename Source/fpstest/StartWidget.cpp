// Fill out your copyright notice in the Description page of Project Settings.


#include "StartWidget.h"

bool UStartWidget::Initialize()
{
	if(!Super::Initialize())
		return false;
	StartBtn=Cast<UButton>(GetWidgetFromName(TEXT("StartBtn")));
	QuitBtn=Cast<UButton>(GetWidgetFromName(TEXT("QuitBtn")));
	if(StartBtn!=nullptr)
		StartBtn->OnClicked.AddDynamic(this,&UStartWidget::OnStartBtnClick);
	if(QuitBtn!=nullptr)
		QuitBtn->OnClicked.AddDynamic(this,&UStartWidget::OnQuitBtnClick);
	return true;
}

void UStartWidget::OnStartBtnClick()
{
	UE_LOG(LogTemp,Warning,TEXT("StartClick"));
}

void UStartWidget::OnQuitBtnClick()
{
	UE_LOG(LogTemp,Warning,TEXT("End"));
}


