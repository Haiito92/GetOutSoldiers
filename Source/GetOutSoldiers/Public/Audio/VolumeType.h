// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(Blueprintable)
enum class EVolumeType : uint8
{
	None = 0,
	Master = 1,
	Music = 2,
	SFX = 3,
	Voices = 4
};
