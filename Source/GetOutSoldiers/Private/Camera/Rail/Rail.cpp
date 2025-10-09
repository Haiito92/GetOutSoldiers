// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/Rail/Rail.h"

#include "Components/SplineComponent.h"


// Sets default values
ARail::ARail()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	m_Spline = CreateDefaultSubobject<USplineComponent>(TEXT("RailSpline"));
}

FVector ARail::GetClosestRailLocation(const FVector& InWorldLocation) const
{
	return m_Spline->FindLocationClosestToWorldLocation(InWorldLocation, ESplineCoordinateSpace::World);
}

