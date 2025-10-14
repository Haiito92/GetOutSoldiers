// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AudioWorldSubsystem.generated.h"

class USoundMix;
class USoundClass;
/**
 * 
 */
UCLASS()
class GETOUTSOLDIERS_API UAudioWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void InitializeAudioSubsystem();
	void StartAudioSubsystem() const;


private:
	UPROPERTY()
	TObjectPtr<USoundMix> m_MainSoundMix;

	UPROPERTY()
	float m_MasterVolume;
	UPROPERTY()
	float m_MusicVolume;
	UPROPERTY()
	float m_SFXVolume;
	UPROPERTY()
	float m_VoicesVolume;
};
