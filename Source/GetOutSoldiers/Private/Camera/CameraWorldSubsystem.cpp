// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraWorldSubsystem.h"

#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraController.h"
#include "Camera/ViewVolumeBlender.h"
#include "Camera/Views/View.h"
#include "Camera/Volumes/ViewVolume.h"

void UCameraWorldSubsystem::InitializeCameraWorldSubsystem(APlayerController* UsedPlayerController)
{
	if (UsedPlayerController == nullptr) return;
	UWorld * World =  GetWorld();
	
	FActorSpawnParameters CameraSpawnParameters;
	CameraSpawnParameters.Name = FName("MainCamera");
	m_MainCamera = World->SpawnActor<ACameraActor>(ACameraActor::StaticClass(), CameraSpawnParameters);
	m_MainCamera->GetCameraComponent()->bConstrainAspectRatio = false;
	UsedPlayerController->SetViewTarget(m_MainCamera);

	TActorRange<AView> Views = TActorRange<AView>(World);
	for (AView* View : Views)
	{
		View->InitView();
	}
	TActorRange<AViewVolume> Volumes = TActorRange<AViewVolume>(World);
	int NextVolumeUId = 0;
	for (AViewVolume* Volume : Volumes)
	{
		Volume->Initialize(NextVolumeUId);
		NextVolumeUId++;
	}
	
	m_CameraController = NewObject<UCameraController>(this);
	m_CameraController->Initialize(m_MainCamera, Views);
	m_ViewVolumeBlender = NewObject<UViewVolumeBlender>(this);
	m_ViewVolumeBlender->Initialize(Volumes);

	m_IsInitialized = true;
}

void UCameraWorldSubsystem::StartCameraWorldSubsystem()
{
	if (!m_IsInitialized) return;
	
	UWorld * World =  GetWorld();
	TActorRange<AView> Views = TActorRange<AView>(World);
	for (AView* View : Views)
	{
		View->StartView();
	}
	TActorRange<AViewVolume> Volumes = TActorRange<AViewVolume>(World);
	for (AViewVolume* Volume : Volumes)
	{
		Volume->Start();
	}

	m_CameraController->Start();
	m_ViewVolumeBlender->Start();
}

void UCameraWorldSubsystem::UpdateCameraWorldSubsystem(float DeltaTime)
{
	if (!m_IsInitialized) return;
	
	m_ViewVolumeBlender->Update(DeltaTime);
	m_CameraController->Update(DeltaTime);
}

void UCameraWorldSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
