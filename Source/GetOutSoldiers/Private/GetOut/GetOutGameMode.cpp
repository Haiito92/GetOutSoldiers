// Fill out your copyright notice in the Description page of Project Settings.


#include "GetOut/GetOutGameMode.h"

void AGetOutGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitializeGame();
}

void AGetOutGameMode::InitializeGame()
{
	CreateLocalPlayers();
	
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

void AGetOutGameMode::CreateLocalPlayers() const
{
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();

	FString OutError;
	GameInstance->CreateLocalPlayer(1, OutError, true);
}
