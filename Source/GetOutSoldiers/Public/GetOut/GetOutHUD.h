// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GoS/GoSHUD.h"
#include "GetOutHUD.generated.h"

class UInteractableUserWidget;
enum EMenuAction : int;
class AGetOutPlayerController;
/**
 * 
 */
UCLASS()
class GETOUTSOLDIERS_API AGetOutHUD : public AGoSHUD
{
	GENERATED_BODY()

public:
	//Cpp function of InitHUD;
	virtual void InitHUD() override;

	UFUNCTION()
	//Distribute Input to BP Class and Current Active Menu Widget
	void OnMenuInputActionPressed(EMenuAction MenuAction);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveOnMenuInputActionPressed(EMenuAction MenuAction);
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UInteractableUserWidget> CurrentInteractionWidget;
};
