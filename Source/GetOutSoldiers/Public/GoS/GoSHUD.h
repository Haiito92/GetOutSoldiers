// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GoSHUD.generated.h"

/**
 * 
 */
UCLASS()
class GETOUTSOLDIERS_API AGoSHUD : public AHUD
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, Category="Initialization")
	void ReceiveInitHUD(AGoSPlayerController* InDriverPlayerController, ANoInputPlayerController* InNoInputPlayerController);
	//Cpp function of InitHUD;
	virtual void InitHUD(AGoSPlayerController* InDriverPlayerController, ANoInputPlayerController* InNoInputPlayerController);
};
