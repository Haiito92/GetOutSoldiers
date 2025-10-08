// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/Views/View.h"

#include "Camera/CameraController.h"


// Sets default values
AView::AView()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AView::InitView()
{
	
}

FCameraConfiguration AView::GetConfiguration() const
{
	FCameraConfiguration CameraConfiguration = FCameraConfiguration();
	CameraConfiguration.SetLocation(GetActorLocation());
	CameraConfiguration.SetRotation(GetActorRotation());
	//TODO Set fov
	
	return CameraConfiguration;
}

void AView::SetActive(bool IsActive)
{
	m_IsActive = IsActive;
	ActivationStateChanged.Broadcast(this, m_IsActive);
}


