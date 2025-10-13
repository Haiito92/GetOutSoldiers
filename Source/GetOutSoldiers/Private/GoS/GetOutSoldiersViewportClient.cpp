// Fill out your copyright notice in the Description page of Project Settings.


#include "GoS/GetOutSoldiersViewportClient.h"
#include "GameFramework/GameUserSettings.h"


void UGetOutSoldiersViewportClient::Draw(FViewport* InViewport, FCanvas* InCanvas)
{
	Super::Draw(InViewport, InCanvas);

	if (!m_IsInitialized)
	{
		GetWindow()->ReshapeWindow(FVector2D(0,30),FVector2D(3840,1000));
		m_IsInitialized = true;
	}
}
