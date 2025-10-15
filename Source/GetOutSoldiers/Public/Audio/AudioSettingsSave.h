// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "AudioSettingsSave.generated.h"

enum class EVolumeType : uint8;
/**
 * 
 */
UCLASS()
class GETOUTSOLDIERS_API UAudioSettingsSave : public USaveGame
{
	GENERATED_BODY()

public:
	UAudioSettingsSave();
	UAudioSettingsSave(const TMap<EVolumeType, float>& InVolumes);

	inline TMap<EVolumeType, float> GetVolumes() const { return m_Volumes; }
	void SetVolumes(const TMap<EVolumeType, float>& InVolumes);

	static const FString SaveSlotName;
	static const int UserIndex;
private:
	UPROPERTY()
	TMap<EVolumeType, float> m_Volumes;
};
