// Fill out your copyright notice in the Description page of Project Settings.


#include "GoS/GetOutSoldiersGameInstance.h"
#include "GameFramework/GameUserSettings.h"

void UGetOutSoldiersGameInstance::Init()
{
	Super::Init();

	UGameUserSettings* Settings = GEngine->GetGameUserSettings();

	if (Settings != nullptr)
	{
		Settings->SetScreenResolution(FIntPoint(640, 480));
		Settings->ApplySettings(true);
		
		Settings->SetFullscreenMode(EWindowMode::Windowed);
		Settings->ApplySettings(true);
	}
}
