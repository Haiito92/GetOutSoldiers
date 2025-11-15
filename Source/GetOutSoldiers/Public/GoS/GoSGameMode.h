// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GoSGameMode.generated.h"

class UGoSGameModeSettings;
class AGoSHUD;
class AGoSPlayerController;
class ANoInputPlayerController;
/**
 * 
 */
UCLASS()
class GETOUTSOLDIERS_API AGoSGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category="Gameloop")
	void ReceiveInitializeGame();
	UFUNCTION(BlueprintCallable, Category="Gameloop")
	void InitializeGame();
	UFUNCTION()
	virtual void InitializeWorldSubsystems();
	
	virtual void FindGameModeSettings();
	
	virtual void CreateLocalPlayers();
	virtual void CreatePawns();
	virtual void CreateHUD();

protected:
	UPROPERTY()
	const UGoSGameModeSettings* m_GameModeSettings;
	
	UPROPERTY(BlueprintReadWrite, Category="Players|PlayerControllers", DisplayName="DriverPlayerController")
	TObjectPtr<AGoSPlayerController> m_DriverPlayerController;
	UPROPERTY(BlueprintReadWrite, Category="Players|PlayerControllers", DisplayName="NounoursPlayerController")
	TObjectPtr<ANoInputPlayerController> m_NounoursPlayerController;
	
	UPROPERTY(BlueprintReadWrite, Category="HUD", DisplayName="GoSHUD")
	TObjectPtr<AGoSHUD> m_GoSHUD;
};
