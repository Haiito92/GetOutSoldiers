// Fill out your copyright notice in the Description page of Project Settings.


#include "Score/HighScoreGameInstanceSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "Score/HighScoresSave.h"
#include "Score/HighScoreSubsystemSettings.h"

FHighScoreStruct::FHighScoreStruct()
{
	Time = 0.0f;
	FormattedTime = "";
}

FHighScoreStruct::FHighScoreStruct(const float& InTime, const FString& InFormattedTime)
{
	Time = InTime;
	FormattedTime = InFormattedTime;
}

FHighScoreStruct::~FHighScoreStruct()
{
}

void UHighScoreGameInstanceSubsystem::InitializeHighScoreGameInstanceSubsystem()
{
	const UHighScoreSubsystemSettings* Settings = GetDefault<UHighScoreSubsystemSettings>();
	if (Settings == nullptr) return;

	m_MaxShownHighScores = Settings->NumberOfShownScores;

	LoadHighScores();
}

void UHighScoreGameInstanceSubsystem::AddHighScore(const float& InTime, const FString& InFormattedTime)
{
	AddHighScore(FHighScoreStruct(InTime, InFormattedTime));
}

void UHighScoreGameInstanceSubsystem::AddHighScore(const FHighScoreStruct& InHighScoreStruct)
{
	m_HighScores.Add(InHighScoreStruct);
	m_HighScores.Sort([](const FHighScoreStruct& A, const FHighScoreStruct& B)
	{
		if (A.Time > B.Time) return false;
		return true;
	});

	while (m_HighScores.Num() > m_MaxShownHighScores)
	{
		
		m_HighScores.RemoveAt(m_HighScores.Num() - 1);
	}
	
	HighScoresChanged.Broadcast();
}

void UHighScoreGameInstanceSubsystem::SaveHighScores() const
{
	if (UHighScoresSave* SettingsSave = Cast<UHighScoresSave>(UGameplayStatics::CreateSaveGameObject(UHighScoresSave::StaticClass())))
	{
		SettingsSave->SetSavedHighScores(m_HighScores);

		UGameplayStatics::AsyncSaveGameToSlot(SettingsSave, UHighScoresSave::SaveSlotName, UHighScoresSave::UserIndex);
	}
}

void UHighScoreGameInstanceSubsystem::LoadHighScores()
{
	if (!UGameplayStatics::DoesSaveGameExist(UHighScoresSave::SaveSlotName,UHighScoresSave::UserIndex)) return;

	FAsyncLoadGameFromSlotDelegate LoadedDelegate;
	// USomeUObjectClass::LoadGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData
	LoadedDelegate.BindUObject(this, &UHighScoreGameInstanceSubsystem::OnHighScoresLoaded);
	UGameplayStatics::AsyncLoadGameFromSlot(UHighScoresSave::SaveSlotName, UHighScoresSave::UserIndex, LoadedDelegate);
}

void UHighScoreGameInstanceSubsystem::OnHighScoresLoaded(const FString& String, int I, USaveGame* SaveGame)
{
	if (UHighScoresSave* SettingsSave = Cast<UHighScoresSave>(SaveGame))
	{
		m_HighScores = SettingsSave->GetSavedHighScores();

		m_HighScores.Sort([](const FHighScoreStruct& A, const FHighScoreStruct& B)
		{
			if (A.Time > B.Time) return false;
			return true;
		});

		while (m_HighScores.Num() > m_MaxShownHighScores)
		{
		
			m_HighScores.RemoveAt(m_HighScores.Num() - 1);
		}
	
		HighScoresChanged.Broadcast();
	}
}
