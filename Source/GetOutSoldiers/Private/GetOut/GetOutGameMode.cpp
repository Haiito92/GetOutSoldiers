// Fill out your copyright notice in the Description page of Project Settings.


#include "GetOut/GetOutGameMode.h"

void AGetOutGameMode::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGetOutGameMode::InitializeGame()
{
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
