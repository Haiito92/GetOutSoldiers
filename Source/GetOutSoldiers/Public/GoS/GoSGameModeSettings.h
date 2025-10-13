// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GoSGameModeSettings.generated.h"

class AGoSHUD;
/**
 * 
 */
UCLASS(Abstract, Config="Game", DefaultConfig)
class GETOUTSOLDIERS_API UGoSGameModeSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category="HUD")
	TSoftClassPtr<AGoSHUD> HUDClass;
};
