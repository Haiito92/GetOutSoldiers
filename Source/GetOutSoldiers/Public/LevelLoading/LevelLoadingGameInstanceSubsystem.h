// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LevelLoadingGameInstanceSubsystem.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FLevelDataRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	FLevelDataRow();
	virtual ~FLevelDataRow() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UWorld> Level = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DisplayName = FText();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> DisplayImage = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool HasNextLevel = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UWorld> NextLevel = nullptr;
};

USTRUCT(BlueprintType)
struct FLevelDataStruct
{
	GENERATED_BODY()

public:
	FLevelDataStruct();
	FLevelDataStruct(const FLevelDataRow& LevelDataRow);
	~FLevelDataStruct();

	UPROPERTY(BlueprintReadOnly)
	FName LevelName = FName();
	UPROPERTY(BlueprintReadOnly)
	FText DisplayName = FText();
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UTexture2D> DisplayImage = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	bool HasNextLevel = false;
	UPROPERTY(BlueprintReadOnly)
	FName NextLevelName = FName();
};

UCLASS()
class GETOUTSOLDIERS_API ULevelLoadingGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void InitializeLevelLoadingGameInstanceSubsystem();

	UFUNCTION(BlueprintCallable)
	void OpenMainMenuLevel() const;

	UFUNCTION(BlueprintCallable)
	void OpenGetOutLevelByIndex(int LevelIndex);
	
	UFUNCTION(BlueprintCallable)
	void OpenNextGetOutLevel();

	UFUNCTION(BlueprintCallable)
	void ReloadCurrentLevel();
protected:
	UFUNCTION(BlueprintCallable)
	void OpenGetOutLevel(const FLevelDataStruct& GetOutLevelData);

	UPROPERTY(BlueprintReadOnly, DisplayName="MainMenuLevelName")
	FLevelDataStruct m_MainMenuLevel;
	UPROPERTY(BlueprintReadOnly, DisplayName="GetOutLevels")
	TArray<FLevelDataStruct> m_GetOutLevels;

	UPROPERTY(BlueprintReadOnly, DisplayName="CurrentGetOutLevel")
	FLevelDataStruct m_CurrentGetOutLevel;
};
