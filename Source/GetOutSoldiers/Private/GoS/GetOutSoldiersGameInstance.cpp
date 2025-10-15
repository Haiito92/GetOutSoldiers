// Fill out your copyright notice in the Description page of Project Settings.


#include "GoS/GetOutSoldiersGameInstance.h"

#include "Audio/AudioGameInstanceSubsystem.h"
#include "Audio/AudioWorldSubsystem.h"
#include "GameFramework/GameUserSettings.h"

void UGetOutSoldiersGameInstance::Init()
{
	Super::Init();

	UGameUserSettings* Settings = GEngine->GetGameUserSettings();
	
	if (Settings != nullptr)
	{
		Settings->SetFullscreenMode(EWindowMode::Windowed);
		Settings->ApplySettings(true);
	}

	if (UAudioGameInstanceSubsystem* AudioGameInstanceSubsystem = GetSubsystem<UAudioGameInstanceSubsystem>())
	{
		AudioGameInstanceSubsystem->InitializeAudioGameInstanceSubsystem();
	}
}

void UGetOutSoldiersGameInstance::OnStart()
{
	Super::OnStart();
}

void UGetOutSoldiersGameInstance::Shutdown()
{
	Super::Shutdown();

	if (UAudioGameInstanceSubsystem* AudioGameInstanceSubsystem = GetSubsystem<UAudioGameInstanceSubsystem>())
	{
		AudioGameInstanceSubsystem->SaveVolumes();
	}
}
