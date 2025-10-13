// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "GetOutSoldiersViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class GETOUTSOLDIERS_API UGetOutSoldiersViewportClient : public UGameViewportClient
{
	GENERATED_BODY()

	virtual void Init(struct FWorldContext& WorldContext, UGameInstance* OwningGameInstance, bool bCreateNewAudioDevice = true) override;
};
