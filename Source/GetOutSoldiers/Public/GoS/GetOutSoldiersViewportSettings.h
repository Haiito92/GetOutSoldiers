// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GetOutSoldiersViewportSettings.generated.h"

/**
 * 
 */
UCLASS(Config="Game", DefaultConfig, meta=(DisplayName="Get Out Soliders Viewport Settings"))
class GETOUTSOLDIERS_API UGetOutSoldiersViewportSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config, EditAnywhere, Category="Window")
	bool UseCustomSize;
	
	UPROPERTY(Config, EditAnywhere, Category="Window")
	FVector2f WindowPosition;
	UPROPERTY(Config, EditAnywhere, Category="Window")
	FVector2f WindowSize;
};
