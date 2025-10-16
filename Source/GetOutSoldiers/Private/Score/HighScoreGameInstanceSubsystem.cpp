// Fill out your copyright notice in the Description page of Project Settings.


#include "Score/HighScoreGameInstanceSubsystem.h"

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
