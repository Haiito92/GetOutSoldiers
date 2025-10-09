// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ViewVolume.generated.h"

class AView;

UCLASS(Abstract)
class GETOUTSOLDIERS_API AViewVolume : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AViewVolume();

	void Initialize(int InUId);
	virtual void Start();

	virtual float ComputeSelfWeight() const;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActivationStateChangedSignature, AViewVolume*, View, bool, IsActive);
	FActivationStateChangedSignature ActivationStateChanged;

	int GetUId() const {return m_UId; }
	int GetPriority() const { return m_Priority; }
	void SetActive(bool IsActive);
	AView* GetView() const {return m_View; }
	
private:
	UPROPERTY()
	int m_UId;
	UPROPERTY(EditAnywhere, DisplayName="Priority")
	int m_Priority;
	UPROPERTY()
	bool m_IsActive;
	UPROPERTY(EditAnywhere, DisplayName="View")
	TObjectPtr<AView> m_View;
};
