// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ViewVolume.h"
#include "GlobalViewVolume.generated.h"

UCLASS()
class GETOUTSOLDIERS_API AGlobalViewVolume : public AViewVolume
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGlobalViewVolume();

	virtual void Start() override;
};
