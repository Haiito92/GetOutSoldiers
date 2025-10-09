// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/Volumes/GlobalViewVolume.h"


// Sets default values
AGlobalViewVolume::AGlobalViewVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AGlobalViewVolume::Start()
{
	Super::Start();

	SetActive(true);
}

