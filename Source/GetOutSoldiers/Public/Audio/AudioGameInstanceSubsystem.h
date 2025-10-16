// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AudioGameInstanceSubsystem.generated.h"

enum class EVolumeType : uint8;
/**
 * 
 */
UCLASS()
class GETOUTSOLDIERS_API UAudioGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void InitializeAudioGameInstanceSubsystem();

	float GetVolume(EVolumeType VolumeType) const;
	bool SetVolume(EVolumeType VolumeType, float Value);

	void SaveVolumes() const;
	void LoadVolumes();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVolumesLoadedSignature);
	UPROPERTY(BlueprintAssignable)
	FVolumesLoadedSignature VolumesLoaded;
	
private:
	void OnAudioSettingsLoaded(const FString& String, int I, USaveGame* SaveGame);
	
	UPROPERTY()
	TMap<EVolumeType, float> m_Volumes;
};
