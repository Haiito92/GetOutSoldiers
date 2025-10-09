// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "UObject/Object.h"
#include "ViewVolumeBlender.generated.h"

class AView;
class AViewVolume;
/**
 * 
 */
UCLASS()
class GETOUTSOLDIERS_API UViewVolumeBlender : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(const TActorRange<AViewVolume>& ViewVolumes) const;
	void Start() const;
	void Update(float DeltaTime);
	
private:
	UFUNCTION()
	void OnVolumeActivationStateChanged(AViewVolume* InVolume, bool InIsActive);
	void AddActiveVolume(AViewVolume* InVolume);
	void RemoveActiveVolume(AViewVolume* InVolume);


	UPROPERTY()
	TArray<TObjectPtr<AViewVolume>> m_ActiveViewVolumes;
	TMap<TObjectPtr<AView>, TArray<TObjectPtr<AViewVolume>>> m_VolumesPerView;
};
