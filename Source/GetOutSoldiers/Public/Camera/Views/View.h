// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "View.generated.h"

struct FCameraConfiguration;

UCLASS(Abstract)
class GETOUTSOLDIERS_API AView : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AView();

	virtual void InitView();
	virtual void StartView();
	
	virtual FCameraConfiguration GetConfiguration() const;

	void SetActive(bool IsActive);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActivationStateChangedSignature, AView*, View, bool, IsActive);
	FActivationStateChangedSignature ActivationStateChanged;

	float GetWeight() const { return m_Weight; }
	void SetWeight(float InWeight) { m_Weight = InWeight; }
	
private:
	UPROPERTY()
	bool m_IsActive;
	UPROPERTY()
	float m_Weight = 1.0f;
};
