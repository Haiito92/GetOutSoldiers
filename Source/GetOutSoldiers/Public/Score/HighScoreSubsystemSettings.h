// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "HighScoreSubsystemSettings.generated.h"

/**
 * 
 */
UCLASS(Config = "Game", DefaultConfig, meta=(DisplayName="HighScore Subsystem Settings"))
class GETOUTSOLDIERS_API UHighScoreSubsystemSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category="HighScores")
	uint32 NumberOfShownScores = 0;
};
