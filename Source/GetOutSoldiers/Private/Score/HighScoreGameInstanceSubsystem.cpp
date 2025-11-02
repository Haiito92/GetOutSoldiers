// Fill out your copyright notice in the Description page of Project Settings.


#include "Score/HighScoreGameInstanceSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "LevelLoading/LevelLoadingGameInstanceSubsystem.h"
#include "LevelLoading/LevelLoadingSubsystemSettings.h"
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

FLevelHighScoresStruct::FLevelHighScoresStruct():
LevelDisplayName(FText()),
HighScores(TArray<FHighScoreStruct>())
{
}

FLevelHighScoresStruct::FLevelHighScoresStruct(const FText& InLevelName):
LevelDisplayName(InLevelName),
HighScores(TArray<FHighScoreStruct>())
{
}

FLevelHighScoresStruct::~FLevelHighScoresStruct()
{
}

void UHighScoreGameInstanceSubsystem::InitializeHighScoreGameInstanceSubsystem()
{
	const ULevelLoadingGameInstanceSubsystem* LevelSubsystem = GetGameInstance()->GetSubsystem<ULevelLoadingGameInstanceSubsystem>();
	if (LevelSubsystem == nullptr) return;

	const TArray<FLevelDataStruct> getOutLevelData = LevelSubsystem->GetGetOutLevelDatas();
	for (FLevelDataStruct LevelData : getOutLevelData)
	{
		m_LevelHighScores.Add(LevelData.LevelName, FLevelHighScoresStruct(LevelData.DisplayName));
	}
	
	const UHighScoreSubsystemSettings* Settings = GetDefault<UHighScoreSubsystemSettings>();
	if (Settings == nullptr) return;

	m_MaxShownHighScores = Settings->NumberOfShownScores;

	LoadHighScores();
}

void UHighScoreGameInstanceSubsystem::AddHighScore(const FName& LevelName, const float& InTime, const FString& InFormattedTime)
{
	AddHighScore(LevelName, FHighScoreStruct(InTime, InFormattedTime));
}

void UHighScoreGameInstanceSubsystem::AddHighScore(const FName& LevelName, const FHighScoreStruct& InHighScoreStruct)
{
	if(!m_LevelHighScores.Contains(LevelName)) return;

	m_LevelHighScores[LevelName].HighScores.Add(InHighScoreStruct);
	
	SortHighScores(m_LevelHighScores[LevelName].HighScores);
	
	HighScoresChanged.Broadcast();
}

void UHighScoreGameInstanceSubsystem::SaveHighScores() const
{
	if (UHighScoresSave* SettingsSave = Cast<UHighScoresSave>(UGameplayStatics::CreateSaveGameObject(UHighScoresSave::StaticClass())))
	{
		SettingsSave->SetSavedHighScores(m_LevelHighScores);

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
		TMap<FName, FLevelHighScoresStruct> SavedHighScores = SettingsSave->GetSavedHighScores();

		for (TPair<FName, FLevelHighScoresStruct> SavedHighScore : SavedHighScores)
		{
			if (m_LevelHighScores.Contains(SavedHighScore.Key))
			{
				m_LevelHighScores[SavedHighScore.Key] = SavedHighScore.Value;
			}
		}
		
		HighScoresChanged.Broadcast();
	}
}

void UHighScoreGameInstanceSubsystem::SortHighScores(TArray<FHighScoreStruct>& HighScores)
{
	HighScores.Sort([](const FHighScoreStruct& A, const FHighScoreStruct& B)
		{
			if (A.Time > B.Time) return false;
			return true;
		});

	while (HighScores.Num() >= m_MaxShownHighScores)
	{
		
		HighScores.RemoveAt(HighScores.Num() - 1);
	}
}
