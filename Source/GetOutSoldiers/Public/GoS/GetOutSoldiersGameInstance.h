// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GetOutSoldiersGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GETOUTSOLDIERS_API UGetOutSoldiersGameInstance : public UGameInstance
{
	GENERATED_BODY()

	virtual void Init() override;
};
