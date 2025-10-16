// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
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
	inline const TArray<FHighScoreStruct>& GetSavedHighScores() const { return m_SavedHighScores; }
	inline void SetSavedHighScores(const TArray<FHighScoreStruct>& InHighScores) { m_SavedHighScores = InHighScores; }
	
	static const FString SaveSlotName;
	static const int UserIndex;
private:
	UPROPERTY();
	TArray<FHighScoreStruct> m_SavedHighScores;
};
