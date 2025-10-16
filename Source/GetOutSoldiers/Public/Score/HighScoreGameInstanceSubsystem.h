// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HighScoreGameInstanceSubsystem.generated.h"

/**
 * 
 */

class UHighScoreSubsystemSettings;

USTRUCT(Blueprintable)
struct FHighScoreStruct
{
	GENERATED_BODY()
public:
	FHighScoreStruct();
	FHighScoreStruct(const float& InTime, const FString& InFormattedTime);
	~FHighScoreStruct();

	UPROPERTY(BlueprintReadWrite)
	float Time;
	UPROPERTY(BlueprintReadWrite)
	FString FormattedTime;
};

UCLASS()
class GETOUTSOLDIERS_API UHighScoreGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void InitializeHighScoreGameInstanceSubsystem();
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHighScoresChangedSignature);
	UPROPERTY(BlueprintAssignable)
	FHighScoresChangedSignature HighScoresChanged;
	
	void AddHighScore(const float& Time, const FString& FormattedTime);
	void AddHighScore(const FHighScoreStruct& InHighScoreStruct);
	
	void SaveHighScores() const;
private:
	void LoadHighScores();
	void OnHighScoresLoaded(const FString& String, int I, USaveGame* SaveGame);

	void SortHighScores();
protected:
	UPROPERTY(BlueprintReadOnly, DisplayName="HighScores")
	TArray<FHighScoreStruct> m_HighScores;
	
private:
	UPROPERTY()
	int m_MaxShownHighScores;
};
