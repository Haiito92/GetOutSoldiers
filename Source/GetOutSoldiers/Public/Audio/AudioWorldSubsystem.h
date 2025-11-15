// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AudioWorldSubsystem.generated.h"

class UAudioGameInstanceSubsystem;
enum class EVolumeType : uint8;
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
	UFUNCTION()
	void InitializeAudioSubsystem();
	void StartAudioSubsystem() const;

	UFUNCTION()
	void OnVolumesLoaded();

	UFUNCTION(BlueprintCallable)
	float GetVolume(EVolumeType VolumeType) const;
	UFUNCTION(BlueprintCallable)
	void SetVolume(EVolumeType VolumeType, float Value);
	
	UFUNCTION(BlueprintCallable)
	USoundClass* GetSoundClass(EVolumeType VolumeType) const;
	

private:
	UPROPERTY()
	TObjectPtr<UAudioGameInstanceSubsystem> m_AudioGameInstanceSubsystem;
	UPROPERTY()
	TObjectPtr<USoundMix> m_MainSoundMix;
	UPROPERTY()
	TMap<EVolumeType, TObjectPtr<USoundClass>> m_SoundClasses;
};
