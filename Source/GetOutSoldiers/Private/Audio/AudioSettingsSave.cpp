// Fill out your copyright notice in the Description page of Project Settings.


#include "Audio/AudioSettingsSave.h"

UAudioSettingsSave::UAudioSettingsSave()
{
	m_Volumes = TMap<EVolumeType, float>();
}

UAudioSettingsSave::UAudioSettingsSave(const TMap<EVolumeType, float>& InVolumes)
{
	SetVolumes(InVolumes);
}

const FString UAudioSettingsSave::SaveSlotName = TEXT("AudioSettingsSave");
const int UAudioSettingsSave::UserIndex = 0;
