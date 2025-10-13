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

private:
	virtual void Draw(FViewport* InViewport, FCanvas* InCanvas) override;

	UPROPERTY()
	bool m_IsInitialized = false;
};
