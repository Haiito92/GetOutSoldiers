// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraWorldSubsystem.h"

#include "Camera/CameraActor.h"
#include "Camera/CameraController.h"
#include "Camera/ViewVolumeBlender.h"
#include "Camera/Views/View.h"
#include "Camera/Volumes/ViewVolume.h"

void UCameraWorldSubsystem::InitializeCameraWorldSubsystem()
{
	UWorld * World =  GetWorld();
	
	FActorSpawnParameters CameraSpawnParameters;
	CameraSpawnParameters.Name = TEXT("MainCamera");
	m_MainCamera = World->SpawnActor<ACameraActor>(ACameraActor::StaticClass(), CameraSpawnParameters);

	m_CameraController = NewObject<UCameraController>(this);
	m_CameraController->Initialize(m_MainCamera, TActorRange<AView>(World));

	m_ViewVolumeBlender = NewObject<UViewVolumeBlender>(this);
	m_ViewVolumeBlender->Initialize(TActorRange<AViewVolume>(World));
}

void UCameraWorldSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_ViewVolumeBlender->Update(DeltaTime);
	m_CameraController->Update(DeltaTime);
}
