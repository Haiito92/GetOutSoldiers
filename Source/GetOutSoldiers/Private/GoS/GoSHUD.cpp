// Fill out your copyright notice in the Description page of Project Settings.


#include "GoS/GoSHUD.h"

#include "GoS/GoSPlayerController.h"
#include "UI/InteractableUserWidget.h"

void AGoSHUD::InitHUD(AGoSPlayerController* InDriverPlayerController, ANoInputPlayerController* InNoInputPlayerController)
{
	ReceiveInitHUD(InDriverPlayerController, InNoInputPlayerController);

	if (InDriverPlayerController != nullptr)
	{
		InDriverPlayerController->OnMenuInputActionPressed.AddDynamic(this, &AGoSHUD::OnMenuInputActionPressed);
	}
}

void AGoSHUD::OnMenuInputActionPressed(EMenuAction MenuAction)
{
	//Call BP Event
	ReceiveOnMenuInputActionPressed(MenuAction);

	//Pass Action to CurrentInteractionWidget;
	if (CurrentInteractionWidget != nullptr)
	{
		CurrentInteractionWidget->HandleMenuAction(MenuAction);
	}	
}