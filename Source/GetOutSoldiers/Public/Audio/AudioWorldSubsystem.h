// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AudioWorldSubsystem.generated.h"

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
	void InitializeAudioSubsystem();
	void StartAudioSubsystem() const;

	UFUNCTION(BlueprintCallable)
	float GetVolume(EVolumeType VolumeType) const;
	UFUNCTION(BlueprintCallable)
	void SetVolume(EVolumeType VolumeType, float Value);
	
	UFUNCTION(BlueprintCallable)
	USoundClass* GetSoundClass(EVolumeType VolumeType) const;
	

private:
	UPROPERTY()
	TObjectPtr<USoundMix> m_MainSoundMix;
	UPROPERTY()
	TMap<EVolumeType, TObjectPtr<USoundClass>> m_SoundClasses;
	UPROPERTY()
	TMap<EVolumeType, float> m_Volumes;
};
