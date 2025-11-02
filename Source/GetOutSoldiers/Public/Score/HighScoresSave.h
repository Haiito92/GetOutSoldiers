// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Score/HighScoreGameInstanceSubsystem.h"
#include "HighScoresSave.generated.h"

struct FHighScoreStruct;
/**
 * 
 */
UCLASS()
class GETOUTSOLDIERS_API UHighScoresSave : public USaveGame
{
	GENERATED_BODY()

public:
	inline const TMap<FName, FLevelHighScoresStruct>& GetSavedHighScores() const { return m_SavedHighScores; }
	inline void SetSavedHighScores(const TMap<FName, FLevelHighScoresStruct>& InHighScores) { m_SavedHighScores = InHighScores; }
	
	static const FString SaveSlotName;
	static const int UserIndex;
private:
	UPROPERTY();
	TMap<FName, FLevelHighScoresStruct> m_SavedHighScores;
};
