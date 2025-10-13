// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GoS/GoSGameModeSettings.h"
#include "GetOutGameModeSettings.generated.h"

class AGetOutHUD;
/**
 * 
 */
UCLASS(Config="Game", DefaultConfig, meta=(DisplayName="GetOut GameMode Settings"))
class GETOUTSOLDIERS_API UGetOutGameModeSettings : public UGoSGameModeSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category="GetOut Pawns")
	TSoftClassPtr<APawn> DriverPawnClass;
};
