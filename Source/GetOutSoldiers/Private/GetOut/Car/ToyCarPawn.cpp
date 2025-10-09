// Fill out your copyright notice in the Description page of Project Settings.


#include "GetOut/Car/ToyCarPawn.h"


// Sets default values
AToyCarPawn::AToyCarPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AToyCarPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToyCarPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AToyCarPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

