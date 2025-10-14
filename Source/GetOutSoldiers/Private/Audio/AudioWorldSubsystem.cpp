// Fill out your copyright notice in the Description page of Project Settings.


#include "Audio/AudioWorldSubsystem.h"

#include "Audio/AudioSubsystemSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundMix.h"
#include "Sound/SoundClass.h"

void UAudioWorldSubsystem::InitializeAudioSubsystem()
{
	const UAudioSubsystemSettings* Settings = GetDefault<UAudioSubsystemSettings>();

	if (Settings == nullptr) return;

	USoundMix* MainSoundMix = Settings->MainSoundMix.LoadSynchronous();
	if (MainSoundMix == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load MainSoundMix"))
		return;
	}
	
	m_MainSoundMix = MainSoundMix;

	m_MasterVolume = 1.0f;
	m_MusicVolume = 1.0f;
	m_SFXVolume = 1.0f;
	m_VoicesVolume = 1.0f;
}

void UAudioWorldSubsystem::StartAudioSubsystem() const
{
	if (m_MainSoundMix == nullptr) return;
	UWorld* World = GetWorld();

	
}
