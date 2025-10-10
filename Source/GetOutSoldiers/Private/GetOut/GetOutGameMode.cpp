// Fill out your copyright notice in the Description page of Project Settings.


#include "GetOut/GetOutGameMode.h"

#include "GameFramework/PlayerStart.h"
#include "GetOut/GetOutGameModeSettings.h"
#include "GetOut/GetOutHUD.h"
#include "GetOut/GetOutPlayerController.h"
#include "GetOut/NoInputPlayerController.h"
#include "Kismet/GameplayStatics.h"

void AGetOutGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitializeGame();
}

void AGetOutGameMode::InitializeGame()
{
	CreateLocalPlayers();
	CreatePawns();
	CreateHUD();
	
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

void AGetOutGameMode::CreateLocalPlayers()
{
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();

	//Get Driver Nounours
	ULocalPlayer* PlayerDriver = GameInstance->GetLocalPlayerByIndex(0);
	m_DriverPlayerController = Cast<AGetOutPlayerController>(PlayerDriver->GetPlayerController(GetWorld()));
	if (m_DriverPlayerController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("GET OUT GAME MODE PLAYER CONTROLLER TYPE IS NOT SUBTYPE OF : AGetOutPlayerController"))
		return;
	}
	
	//Setup Nounours Player
	FString OutError;
	ULocalPlayer* PlayerNounours = GameInstance->CreateLocalPlayer(1, OutError, false);
	m_NounoursPlayerController = GetWorld()->SpawnActor<ANoInputPlayerController>();
	PlayerNounours->PlayerController = m_NounoursPlayerController;
	m_NounoursPlayerController->Player = PlayerNounours;
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

void AGetOutGameMode::CreateHUD()
{
	const UGetOutGameModeSettings* Settings = GetDefault<UGetOutGameModeSettings>();

	if (Settings->GetOutHUDClass ==  nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("GetOut HUD Class not set in GetOut GameMode Settings"))
		return;
	}

	UClass* GetOutHUDUClass = Settings->GetOutHUDClass.LoadSynchronous();
	FVector Location = FVector::Zero();
	m_GetOutHUD = Cast<AGetOutHUD>(GetWorld()->SpawnActor(GetOutHUDUClass, &Location));

	if (m_GetOutHUD == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't Spawn GetOut HUD"))
		return;
	}

	if (m_DriverPlayerController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Driver Player Controller is nullptr. Can't set its HUD."))
		return;
	}
	m_DriverPlayerController->MyHUD = m_GetOutHUD;
	m_GetOutHUD->PlayerOwner = m_DriverPlayerController;
}
