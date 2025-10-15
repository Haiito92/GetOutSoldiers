// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GoSHUD.generated.h"

enum EMenuAction : int;
class UInteractableUserWidget;
/**
 * 
 */
UCLASS()
class GETOUTSOLDIERS_API AGoSHUD : public AHUD
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, Category="Initialization")
	void ReceiveInitHUD(AGoSPlayerController* InDriverPlayerController, ANoInputPlayerController* InNoInputPlayerController);
	//Cpp function of InitHUD;
	virtual void InitHUD(AGoSPlayerController* InDriverPlayerController, ANoInputPlayerController* InNoInputPlayerController);

	UFUNCTION()
	//Distribute Input to BP Class and Current Active Menu Widget
	void OnMenuInputActionPressed(EMenuAction MenuAction);

	UFUNCTION(BlueprintCallable)
	void SetCurrentInteractionWidget(UInteractableUserWidget* InWidget);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveOnMenuInputActionPressed(EMenuAction MenuAction);

private:
	UPROPERTY()
	TObjectPtr<UInteractableUserWidget> CurrentInteractionWidget;
};
