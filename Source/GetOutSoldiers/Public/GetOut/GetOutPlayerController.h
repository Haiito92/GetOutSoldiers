// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GoS/GoSPlayerController.h"
#include "GetOutPlayerController.generated.h"

/**
 * 
 */

UENUM(Blueprintable)
enum EMenuAction
{
	None = 0,
	GoUp = 1,
	GoDown = 2,
	GoLeft = 3,
	GoRight = 4,
	Interact = 5,
};

UCLASS()
class GETOUTSOLDIERS_API AGetOutPlayerController : public AGoSPlayerController
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMenuInputActionPressed, EMenuAction, MenuAction);
	UPROPERTY(BlueprintCallable)
	FOnMenuInputActionPressed OnMenuInputActionPressed;
};
