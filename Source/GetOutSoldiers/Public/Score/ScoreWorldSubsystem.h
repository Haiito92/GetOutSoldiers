// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ScoreWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class GETOUTSOLDIERS_API UScoreWorldSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitializeScoreWorldSubsystem();
	UFUNCTION(BlueprintCallable)
	void StartScoreWorldSubsystem();
	UFUNCTION(BlueprintCallable)
	void PauseScoreWorldSubsystem();
	UFUNCTION(BlueprintCallable)
	void UnpauseScoreWorldSubsystem();
	UFUNCTION(BlueprintCallable)
	void EndScoreWorldSubsystem();
	UFUNCTION(BlueprintCallable)
	void ResetScoreWorldSubsystem();

	UFUNCTION(BlueprintCallable)
	void SaveScore() const;

	UFUNCTION(BlueprintCallable)
	inline float GetTimerValue() const { return m_ScoreTimer; }
	UFUNCTION(BlueprintCallable)
	inline FString GetFormattedTimer() const { return m_FormattedTimer; }
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTimerChangedSignature, float, TimerValue);
	UPROPERTY(BlueprintAssignable)
	FTimerChangedSignature TimerChanged;

private:
	virtual TStatId GetStatId() const override { return TStatId(); };
	virtual void Tick(float DeltaTime) override;

	void UpdateFormattedTimer();
	
	UPROPERTY()
	float m_ScoreTimer;
	UPROPERTY()
	FString m_FormattedTimer;
	UPROPERTY()
	bool m_IsScoreSystemActive;
};
