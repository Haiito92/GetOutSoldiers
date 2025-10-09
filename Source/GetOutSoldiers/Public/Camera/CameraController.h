// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "UObject/Object.h"
#include "CameraController.generated.h"

class UCameraSubsystemSettings;
class AView;
/**
 * 
 */

USTRUCT()
struct FCameraConfiguration
{
	GENERATED_BODY()
	~FCameraConfiguration() = default;

public:
	FVector GetLocation() const { return Pivot; }
	void SetLocation(const FVector& InLocation) { Pivot = InLocation; }
	FRotator GetRotation() const { return FRotator(Pitch, Yaw, Roll); }
	void SetRotation(const FRotator& InRotator) {Yaw = InRotator.Yaw; Pitch = InRotator.Pitch; Roll = InRotator.Roll; }
	
	UPROPERTY()
	float Yaw = 0.0f;
	UPROPERTY()
	float Pitch = 0.0f;
	UPROPERTY()
	float Roll = 0.0f;

	UPROPERTY()
	FVector Pivot = FVector::Zero();

	UPROPERTY()
	float FoV = 0.0f;
};

UCLASS()
class GETOUTSOLDIERS_API UCameraController : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(ACameraActor* InCamera, const TActorRange<AView>& InViews);
	void Start();
	void Update(float DeltaTime);

private:
	UFUNCTION()
	void OnViewActivationStateChanged(AView* InView, bool InIsActive);
	void AddActiveView(AView* InView);
	void RemoveActiveView(AView* InView);

	FCameraConfiguration ComputeAverageConfiguration() const;
	void LerpCurrentConfiguration(float DeltaTime);
	void ApplyCurrentConfiguration() const;


	UPROPERTY()
	const UCameraSubsystemSettings* m_CameraSubsystemSettings; 
	
	UPROPERTY()
	TObjectPtr<ACameraActor> m_Camera;
	UPROPERTY()
	TArray<TObjectPtr<AView>> m_ActiveViews;

	UPROPERTY()
	FCameraConfiguration m_CurrentConfiguration;
	UPROPERTY()
	FCameraConfiguration m_TargetConfiguration;
};
