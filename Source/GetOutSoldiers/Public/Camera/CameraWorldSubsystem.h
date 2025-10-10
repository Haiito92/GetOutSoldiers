// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CameraWorldSubsystem.generated.h"

class UViewVolumeBlender;
class UCameraController;
/**
 * 
 */
UCLASS()
class GETOUTSOLDIERS_API UCameraWorldSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="Camera Subsystem")
	void InitializeCameraWorldSubsystem(APlayerController* UsedPlayerController);
	UFUNCTION(BlueprintCallable, Category="Camera Subsystem")
	void StartCameraWorldSubsystem();
	UFUNCTION(BlueprintCallable, Category="Camera Subsystem")
	void UpdateCameraWorldSubsystem(float DeltaTime);

private:
	virtual TStatId GetStatId() const override { return TStatId(); };
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	bool m_IsInitialized = false;
	
	UPROPERTY()
	TObjectPtr<ACameraActor> m_MainCamera;
	
	UPROPERTY()
	TObjectPtr<UCameraController> m_CameraController;
	
	UPROPERTY()
	TObjectPtr<UViewVolumeBlender> m_ViewVolumeBlender;
};
