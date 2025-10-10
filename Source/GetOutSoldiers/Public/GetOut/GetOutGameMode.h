// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GetOutGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GETOUTSOLDIERS_API AGetOutGameMode : public AGameModeBase
{
	GENERATED_BODY()

	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent, Category="Gameloop")
	void ReceiveInitializeGame();
	UFUNCTION(BlueprintCallable, Category="Gameloop")
	void InitializeGame();
	
	UFUNCTION(BlueprintImplementableEvent, Category="Gameloop")
	void ReceiveStartGame();
	UFUNCTION(BlueprintCallable, Category="Gameloop")
	void StartGame();
	
	UFUNCTION(BlueprintImplementableEvent, Category="Gameloop")
	void ReceiveEndGame();
	UFUNCTION(BlueprintCallable, Category="Gameloop")
	void EndGame();
	
	UFUNCTION(BlueprintImplementableEvent, Category="Gameloop")
	void ReceivePauseGame();
	UFUNCTION(BlueprintCallable, Category="Gameloop")
	void PauseGame();
	
	UFUNCTION(BlueprintImplementableEvent, Category="Gameloop")
	void ReceiveUnpauseGame();
	UFUNCTION(BlueprintCallable, Category="Gameloop")
	void UnpauseGame();
	
	UFUNCTION(BlueprintImplementableEvent, Category="Gameloop")
	void ReceiveRestartGame();
	UFUNCTION(BlueprintCallable, Category="Gameloop")
	void RestartGame();
	
	UFUNCTION(BlueprintImplementableEvent, Category="Gameloop")
	void ReceiveLeaveGame();
	UFUNCTION(BlueprintCallable, Category="Gameloop")
	void LeaveGame();

private:
	void CreateLocalPlayers() const;
};
