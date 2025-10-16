// Fill out your copyright notice in the Description page of Project Settings.


#include "Score/ScoreWorldSubsystem.h"

#include "MathUtil.h"
#include "Kismet/KismetMathLibrary.h"
#include "Score/HighScoreGameInstanceSubsystem.h"

void UScoreWorldSubsystem::InitializeScoreWorldSubsystem()
{
	m_ScoreTimer = 0.0f;
	UpdateFormattedTimer();
}

void UScoreWorldSubsystem::StartScoreWorldSubsystem()
{
	m_IsScoreSystemActive = true;
}

void UScoreWorldSubsystem::PauseScoreWorldSubsystem()
{
	m_IsScoreSystemActive = false;
}

void UScoreWorldSubsystem::UnpauseScoreWorldSubsystem()
{
	m_IsScoreSystemActive = true;
}

void UScoreWorldSubsystem::EndScoreWorldSubsystem()
{
	m_IsScoreSystemActive = false;
	UpdateFormattedTimer();
	SaveScore();
}

void UScoreWorldSubsystem::ResetScoreWorldSubsystem()
{
	m_ScoreTimer = 0.0f;
	m_IsScoreSystemActive = false;
	UpdateFormattedTimer();
}

void UScoreWorldSubsystem::SaveScore() const
{
	UHighScoreGameInstanceSubsystem* HighScoreGameInstanceSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UHighScoreGameInstanceSubsystem>();
	if (HighScoreGameInstanceSubsystem == nullptr) return;
	HighScoreGameInstanceSubsystem->AddHighScore(m_ScoreTimer, m_FormattedTimer);
}

void UScoreWorldSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_IsScoreSystemActive)
	{
		m_ScoreTimer += DeltaTime;
		UpdateFormattedTimer();
		TimerChanged.Broadcast(m_ScoreTimer);
	}
}

void UScoreWorldSubsystem::UpdateFormattedTimer()
{
	float Seconds = 0.0f;
	int32 Minutes = UKismetMathLibrary::FMod(m_ScoreTimer, 60.f, Seconds);
	int32 SecondsInt = Seconds;

	FString MinutesString,SecondsString;
	if (Minutes < 10)
	{
		MinutesString = FString::Format(TEXT("0{0}"), {Minutes});
	}
	else
	{
		MinutesString = FString::Format(TEXT("{0}"), {Minutes});
	}

	if (SecondsInt < 10)
	{
		SecondsString = FString::Format(TEXT("0{0}"), {SecondsInt});
	}
	else
	{
		SecondsString = FString::Format(TEXT("{0}"), {SecondsInt});
	}

	m_FormattedTimer = FString::Format(TEXT("{0}:{1}"), {MinutesString, SecondsString});
}
