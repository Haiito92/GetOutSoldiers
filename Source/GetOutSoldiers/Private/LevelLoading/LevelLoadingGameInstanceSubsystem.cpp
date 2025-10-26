// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelLoading/LevelLoadingGameInstanceSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "LevelLoading/LevelLoadingSubsystemSettings.h"
#include "Tests/AutomationCommon.h"

FLevelDataRow::FLevelDataRow()
{
}

FLevelDataRow::~FLevelDataRow()
{
}

FLevelDataStruct::FLevelDataStruct()
{
}

FLevelDataStruct::FLevelDataStruct(const FLevelDataRow& LevelDataRow):
LevelName(FName(*FPackageName::ObjectPathToPackageName(LevelDataRow.Level.ToString()))),
DisplayName(LevelDataRow.DisplayName),
DisplayImage(LevelDataRow.DisplayImage.LoadSynchronous()),
HasNextLevel(LevelDataRow.HasNextLevel),
NextLevelName(FName(*FPackageName::ObjectPathToPackageName(LevelDataRow.NextLevel.ToString())))
{
}

FLevelDataStruct::~FLevelDataStruct()
{
}

void ULevelLoadingGameInstanceSubsystem::InitializeLevelLoadingGameInstanceSubsystem()
{
	const ULevelLoadingSubsystemSettings* Settings = GetDefault<ULevelLoadingSubsystemSettings>();
	if (!Settings) return;

	UDataTable* GetOutLevelDataTable = Settings->GetOutLevels.LoadSynchronous();

	if (!GetOutLevelDataTable->GetRowStruct()->IsChildOf(FLevelDataRow::StaticStruct()))
	{
		UE_LOG(LogTemp, Log, TEXT("Couldn't load level data table because struct is not of type FLevelDataRow"));
		return;
	}

	m_MainMenuLevel.LevelName = FName(*FPackageName::ObjectPathToPackageName(Settings->MainMenuLevel.ToString()));
	
	for (TPair<FName, unsigned char*> Row : GetOutLevelDataTable->GetRowMap())
	{
		FLevelDataRow* LevelData = reinterpret_cast<FLevelDataRow*>(Row.Value);

		m_GetOutLevels.Add(FLevelDataStruct(*LevelData));
	}
}

void ULevelLoadingGameInstanceSubsystem::OpenMainMenuLevel() const
{
	UGameplayStatics::OpenLevel(this, m_MainMenuLevel.LevelName);
}

void ULevelLoadingGameInstanceSubsystem::OpenGetOutLevelByIndex(int LevelIndex)
{
	if (m_GetOutLevels.IsValidIndex(LevelIndex))
	{
		OpenGetOutLevel(m_GetOutLevels[LevelIndex]);
	}
}

void ULevelLoadingGameInstanceSubsystem::OpenNextGetOutLevel()
{
	if (!m_CurrentGetOutLevel.HasNextLevel) return;

	FLevelDataStruct* NextLevel = m_GetOutLevels.FindByPredicate([&](const FLevelDataStruct& LevelDataStruct)
	{
		return LevelDataStruct.LevelName == m_CurrentGetOutLevel.NextLevelName;
	});

	if (NextLevel)
	{
		OpenGetOutLevel(*NextLevel);
	}else
	{
		OpenMainMenuLevel();
	}
}

void ULevelLoadingGameInstanceSubsystem::ReloadCurrentLevel()
{
	UGameplayStatics::OpenLevel(this, FName(UGameplayStatics::GetCurrentLevelName(this)));
}

void ULevelLoadingGameInstanceSubsystem::OpenGetOutLevel(const FLevelDataStruct& GetOutLevelData)
{
	m_CurrentGetOutLevel = GetOutLevelData;
	UGameplayStatics::OpenLevel(this, m_CurrentGetOutLevel.LevelName);
}


