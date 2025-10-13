// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GoS/GoSGameModeSettings.h"
#include "MainMenuGameModeSettings.generated.h"

/**
 * 
 */
UCLASS(Config="Game", DefaultConfig, meta=(DisplayName="Main Menu GameMode Settings"))
class GETOUTSOLDIERS_API UMainMenuGameModeSettings : public UGoSGameModeSettings
{
	GENERATED_BODY()
};
