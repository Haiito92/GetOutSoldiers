// Fill out your copyright notice in the Description page of Project Settings.


#include "GetOut/GetOutGameMode.h"

#include "GameFramework/PlayerStart.h"
#include "GetOut/GetOutGameModeSettings.h"
#include "GetOut/GetOutHUD.h"
#include "GetOut/GetOutPlayerController.h"
#include "GetOut/NoInputPlayerController.h"
#include "Kismet/GameplayStatics.h"



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

void AGetOutGameMode::FindGameModeSettings()
{
	m_GameModeSettings = GetDefault<UGetOutGameModeSettings>();	
}

void AGetOutGameMode::CreatePawns()
{
	if (m_DriverPlayerController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Driver Player Controller is nullptr"))
		return;
	}

	APlayerStart* PlayerStart = Cast<APlayerStart>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()));
	if (PlayerStart == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Player Start in the scene"))
		return;
	}

	const UGetOutGameModeSettings* Settings = GetDefault<UGetOutGameModeSettings>();
	if (Settings->DriverPawnClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Driver Pawn Class not set in GetOut GameMode settings"))
		return;
	}
	UClass* DrivePawnUClass = Settings->DriverPawnClass.LoadSynchronous();
	const FTransform SpawnPoint = PlayerStart->GetActorTransform();

	m_DriverPawn = Cast<APawn>(GetWorld()->SpawnActor(DrivePawnUClass, &SpawnPoint));

	m_DriverPlayerController->Possess(m_DriverPawn);
}
