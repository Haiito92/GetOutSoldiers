// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "LevelLoadingSubsystemSettings.generated.h"

/**
 * 
 */
UCLASS(Config = "Game", DefaultConfig, meta = (DisplayName = "Level Loading Subsystem Settings"))
class GETOUTSOLDIERS_API ULevelLoadingSubsystemSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category="Levels")
	TSoftObjectPtr<UWorld> MainMenuLevel;
	
	UPROPERTY(Config, EditAnywhere, Category="Levels")
	TSoftObjectPtr<UDataTable> GetOutLevels;
};
