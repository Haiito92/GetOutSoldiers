// Fill out your copyright notice in the Description page of Project Settings.


#include "GoS/GoSGameMode.h"

#include "GetOut/GetOutPlayerController.h"
#include "GetOut/NoInputPlayerController.h"
#include "GoS/GoSGameModeSettings.h"
#include "GoS/GoSHUD.h"

void AGoSGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitializeGame();
}

void AGoSGameMode::InitializeGame()
{
	FindGameModeSettings();
	
	CreateLocalPlayers();
	CreatePawns();
	CreateHUD();
	
	ReceiveInitializeGame();
}

void AGoSGameMode::FindGameModeSettings()
{
	
}

void AGoSGameMode::CreateLocalPlayers()
{
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();

	//Get Driver Nounours
	ULocalPlayer* PlayerDriver = GameInstance->GetLocalPlayerByIndex(0);
	m_DriverPlayerController = Cast<AGoSPlayerController>(PlayerDriver->GetPlayerController(GetWorld()));
	if (m_DriverPlayerController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("GET OUT GAME MODE PLAYER CONTROLLER TYPE IS NOT SUBTYPE OF : AGoSPlayerController"))
		return;
	}
	
	//Setup Nounours Player
	FString OutError;
	ULocalPlayer* PlayerNounours = GameInstance->CreateLocalPlayer(1, OutError, false);
	m_NounoursPlayerController = GetWorld()->SpawnActor<ANoInputPlayerController>();
	PlayerNounours->PlayerController = m_NounoursPlayerController;
	m_NounoursPlayerController->Player = PlayerNounours;
}

void AGoSGameMode::CreatePawns()
{
}

void AGoSGameMode::CreateHUD()
{
	if (m_GameModeSettings == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Settings ptr == nullptr"))
		return;
	}
	
	if (m_GameModeSettings->HUDClass ==  nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("HUD Class not set in GameMode Settings"))
		return;
	}
	UClass* GoSHUDUClass = m_GameModeSettings->HUDClass.LoadSynchronous();
	if (GoSHUDUClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't load GoS HUD Class"))
		return;
	}
	
	FVector Location = FVector::Zero();
	m_GoSHUD = Cast<AGoSHUD>(GetWorld()->SpawnActor(GoSHUDUClass, &Location));

	if (m_GoSHUD == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't Spawn GoS HUD"))
		return;
	}

	if (m_DriverPlayerController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Driver Player Controller is nullptr. Can't set its HUD."))
		return;
	}
	m_DriverPlayerController->MyHUD = m_GoSHUD;
	m_GoSHUD->PlayerOwner = m_DriverPlayerController;
	m_GoSHUD->InitHUD(m_DriverPlayerController, m_NounoursPlayerController);
}
