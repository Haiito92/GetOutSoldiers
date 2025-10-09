// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/Views/FixedView.h"


// Sets default values
AFixedView::AFixedView()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AFixedView::StartView()
{
	Super::StartView();

	// SetActive(true);
}

