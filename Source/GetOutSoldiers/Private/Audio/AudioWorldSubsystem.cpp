// Fill out your copyright notice in the Description page of Project Settings.


#include "Audio/AudioWorldSubsystem.h"

#include "MathUtil.h"
#include "Audio/AudioSubsystemSettings.h"
#include "Sound/SoundMix.h"
#include "Sound/SoundClass.h"
#include "Audio/VolumeType.h"
#include "Kismet/GameplayStatics.h"

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

	for (TPair<EVolumeType, TSoftObjectPtr<USoundClass>> VolumeSoundClassPair : Settings->SoundClasses)
	{
		USoundClass* SoundClass = VolumeSoundClassPair.Value.LoadSynchronous();
		
		if (SoundClass == nullptr) continue;
		
		m_SoundClasses.Add(VolumeSoundClassPair.Key, SoundClass);
		m_Volumes.Add(VolumeSoundClassPair.Key, 1.0f);
	}
}

void UAudioWorldSubsystem::StartAudioSubsystem() const
{
	if (m_MainSoundMix == nullptr) return;
	UWorld* World = GetWorld();

	UGameplayStatics::PushSoundMixModifier(World, m_MainSoundMix);

	for (TPair<EVolumeType, TObjectPtr<USoundClass>> Pair : m_SoundClasses)
	{
		float Volume = GetVolume(Pair.Key);
		if (Volume == -1.0f) continue;
		
		UGameplayStatics::SetSoundMixClassOverride(World, m_MainSoundMix, Pair.Value, Volume);
	}
}

float UAudioWorldSubsystem::GetVolume(EVolumeType VolumeType) const
{
	if (!m_Volumes.Contains(VolumeType)) return -1.0f;
	
	return m_Volumes[VolumeType];
}

void UAudioWorldSubsystem::SetVolume(EVolumeType VolumeType, float Value)
{
	if (!m_Volumes.Contains(VolumeType)) return;

	float ClampedValue = FMathf::Clamp(Value, 0.0f, 1.0f);
	m_Volumes[VolumeType] = ClampedValue;

	if (m_MainSoundMix == nullptr) return;
	
	USoundClass* SoundClass = GetSoundClass(VolumeType);
	if (SoundClass == nullptr) return;

	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), m_MainSoundMix, SoundClass, ClampedValue);
}

USoundClass* UAudioWorldSubsystem::GetSoundClass(EVolumeType VolumeType) const
{
	if (!m_SoundClasses.Contains(VolumeType)) return nullptr;

	return m_SoundClasses[VolumeType];
}
