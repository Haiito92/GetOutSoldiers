// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/Volumes/ViewVolume.h"


// Sets default values
AViewVolume::AViewVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AViewVolume::Initialize(int InUId)
{
	m_UId = InUId;
}

void AViewVolume::Start()
{
}

float AViewVolume::ComputeSelfWeight() const
{
	return 1.0f;
}

void AViewVolume::SetActive(bool IsActive)
{
	m_IsActive = IsActive;
	ActivationStateChanged.Broadcast(this, IsActive);
}

