// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/MainMenuGameMode.h"

#include "MainMenu/MainMenuGameModeSettings.h"

void AMainMenuGameMode::FindGameModeSettings()
{
	m_GameModeSettings = GetDefault<UMainMenuGameModeSettings>();
}
