// Fill out your copyright notice in the Description page of Project Settings.


#include "GetOut/GetOutGameMode.h"

void AGetOutGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitializeGame();
}

void AGetOutGameMode::InitializeGame()
{
	// const UGetOutDeveloperSettings* GetOutDeveloperSettings = GetDefault<UGetOutDeveloperSettings>();
	// UWorld* World = GetWorld();
	// UGameInstance* GameInstance = GetGameInstance();
	//
	// //Create Players
	// FString OutError;
	// ULocalPlayer* PlayerZero = GameInstance->CreateLocalPlayer(0, OutError, true);
	// ULocalPlayer* PlayerOne = GameInstance->CreateLocalPlayer(1, OutError, true);
	//
	// //SpawnPawns
	
	
	ReceiveInitializeGame();
}

void AGetOutGameMode::StartGame()
{
	ReceiveStartGame();
}

void AGetOutGameMode::EndGame()
{
	ReceiveEndGame();
}

void AGetOutGameMode::PauseGame()
{
	ReceivePauseGame();
}

void AGetOutGameMode::UnpauseGame()
{
	ReceiveUnpauseGame();
}

void AGetOutGameMode::RestartGame()
{
	ReceiveRestartGame();
}

void AGetOutGameMode::LeaveGame()
{
	ReceiveLeaveGame();
}
