// Fill out your copyright notice in the Description page of Project Settings.


#include "Audio/AudioGameInstanceSubsystem.h"

#include "MathUtil.h"
#include "Audio/AudioSettingsSave.h"
#include "Audio/AudioSubsystemSettings.h"
#include "Kismet/GameplayStatics.h"

void UAudioGameInstanceSubsystem::InitializeAudioGameInstanceSubsystem()
{
	const UAudioSubsystemSettings* Settings = GetDefault<UAudioSubsystemSettings>();

	if (Settings == nullptr) return;

	for (TPair<EVolumeType, TSoftObjectPtr<USoundClass>> VolumeSoundClassPair : Settings->SoundClasses)
	{
		m_Volumes.Add(VolumeSoundClassPair.Key, 1.0f);
	}

	LoadVolumes();
}

float UAudioGameInstanceSubsystem::GetVolume(EVolumeType VolumeType) const
{
	if (!m_Volumes.Contains(VolumeType)) return -1.0f;
	
	return m_Volumes[VolumeType];
}

bool UAudioGameInstanceSubsystem::SetVolume(EVolumeType VolumeType, float Value)
{
	if (!m_Volumes.Contains(VolumeType)) return false;
	
	float ClampedValue = FMathf::Clamp(Value, 0.0f, 1.0f);
	m_Volumes[VolumeType] = ClampedValue;

	return true;
}

void UAudioGameInstanceSubsystem::SaveVolumes() const
{
	if (UAudioSettingsSave* SettingsSave = Cast<UAudioSettingsSave>(UGameplayStatics::CreateSaveGameObject(UAudioSettingsSave::StaticClass())))
	{
		SettingsSave->SetVolumes(m_Volumes);

		UGameplayStatics::AsyncSaveGameToSlot(SettingsSave, UAudioSettingsSave::SaveSlotName, UAudioSettingsSave::UserIndex);
	}
}

void UAudioGameInstanceSubsystem::LoadVolumes()
{
	if (!UGameplayStatics::DoesSaveGameExist(UAudioSettingsSave::SaveSlotName,UAudioSettingsSave::UserIndex)) return;

	FAsyncLoadGameFromSlotDelegate LoadedDelegate;
	// USomeUObjectClass::LoadGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData
	LoadedDelegate.BindUObject(this, &UAudioGameInstanceSubsystem::OnAudioSettingsLoaded);
	UGameplayStatics::AsyncLoadGameFromSlot(UAudioSettingsSave::SaveSlotName, UAudioSettingsSave::UserIndex, LoadedDelegate);
}

void UAudioGameInstanceSubsystem::OnAudioSettingsLoaded(const FString& String, int I, USaveGame* SaveGame)
{
	if (UAudioSettingsSave* SettingsSave = Cast<UAudioSettingsSave>(SaveGame))
	{
		for (TPair<EVolumeType,float> Pair : SettingsSave->GetVolumes())
		{
			if (m_Volumes.Contains(Pair.Key))
			{
				m_Volumes[Pair.Key] = Pair.Value;
			}
		}
	}
}
