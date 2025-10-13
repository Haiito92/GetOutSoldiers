// Fill out your copyright notice in the Description page of Project Settings.


#include "GoS/GetOutSoldiersViewportClient.h"
#include "GameFramework/GameUserSettings.h"
#include "GoS/GetOutSoldiersViewportSettings.h"


void UGetOutSoldiersViewportClient::Draw(FViewport* InViewport, FCanvas* InCanvas)
{
	Super::Draw(InViewport, InCanvas);

	if (m_IsInitialized) return;
	
	const UGetOutSoldiersViewportSettings* Settings = GetDefault<UGetOutSoldiersViewportSettings>();

	if (!Settings->UseCustomSize) return;
	
	GetWindow()->ReshapeWindow( Settings->WindowPosition, Settings->WindowSize);
	m_IsInitialized = true;
}
