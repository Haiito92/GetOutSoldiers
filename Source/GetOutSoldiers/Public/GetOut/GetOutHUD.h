// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GoS/GoSHUD.h"
#include "GetOutHUD.generated.h"

class UInteractableUserWidget;
enum EMenuAction : int;
class AGetOutPlayerController;
/**
 * 
 */
UCLASS()
class GETOUTSOLDIERS_API AGetOutHUD : public AGoSHUD
{
	GENERATED_BODY()

public:
	//Cpp function of InitHUD;
	virtual void InitHUD(AGoSPlayerController* InDriverPlayerController, ANoInputPlayerController* InNoInputPlayerController) override;
};
