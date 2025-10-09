// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/Views/DollyView.h"

#include "Camera/CameraController.h"
#include "Camera/Rail/Rail.h"
#include "GetOut/Car/ToyCarPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ADollyView::ADollyView()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ADollyView::StartView()
{
	Super::StartView();

	if (m_TargetType == EDollyViewTargetType::Class)
	{
		m_Target = UGameplayStatics::GetActorOfClass(GetWorld(), AToyCarPawn::StaticClass());
	}
}

FCameraConfiguration ADollyView::GetConfiguration() const
{
	FCameraConfiguration CameraConfiguration = FCameraConfiguration();
	CameraConfiguration.SetLocation(m_Rail->GetClosestRailLocation(m_Target->GetActorLocation()));
	CameraConfiguration.SetRotation(UKismetMathLibrary::FindLookAtRotation(CameraConfiguration.GetLocation(), m_Target->GetActorLocation()));
	
	return CameraConfiguration;
}

