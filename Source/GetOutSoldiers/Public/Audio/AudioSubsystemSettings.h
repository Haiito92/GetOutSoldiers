// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "AudioSubsystemSettings.generated.h"

enum class EVolumeType : uint8;
class USoundMix;
/**
 * 
 */
UCLASS(Config="Game", DefaultConfig, meta=(DisplayName="Audio Subsystem Settings"))
class GETOUTSOLDIERS_API UAudioSubsystemSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category="Sound Mix")
	TSoftObjectPtr<USoundMix> MainSoundMix;

	UPROPERTY(Config, EditAnywhere, Category="Sound Classes")
	TMap<EVolumeType, TSoftObjectPtr<USoundClass>> SoundClasses;
};
