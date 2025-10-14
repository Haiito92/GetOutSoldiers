// Fill out your copyright notice in the Description page of Project Settings.


#include "GetOut/GetOutHUD.h"

#include "GetOut/GetOutPlayerController.h"
#include "UI/InteractableUserWidget.h"

void AGetOutHUD::InitHUD(AGoSPlayerController* InDriverPlayerController, ANoInputPlayerController* InNoInputPlayerController)
{
	if (AGetOutPlayerController* GetOutPlayerController = Cast<AGetOutPlayerController>(PlayerOwner))
	{
		GetOutPlayerController->OnMenuInputActionPressed.AddDynamic(this, &AGetOutHUD::OnMenuInputActionPressed);
	}

	Super::InitHUD(InDriverPlayerController, InNoInputPlayerController);
}
