// Fill out your copyright notice in the Description page of Project Settings.


#include "GoS/GetOutSoldiersViewportClient.h"

#include "GameFramework/GameUserSettings.h"

void UGetOutSoldiersViewportClient::Init(struct FWorldContext& WorldContext, UGameInstance* OwningGameInstance,
                                         bool bCreateNewAudioDevice)
{
	Super::Init(WorldContext, OwningGameInstance, bCreateNewAudioDevice);

	UGameUserSettings* Settings = GEngine->GetGameUserSettings();

	if (Settings != nullptr)
	{
		Settings->SetScreenResolution(FIntPoint(3840, 1080));
		Settings->SetFullscreenMode(EWindowMode::Windowed);
		
		Settings->ApplySettings(true);
	}
}
