// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/Views/DollyView.h"

#include "Camera/CameraController.h"
#include "Camera/Rail/Rail.h"
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
		m_Target = UGameplayStatics::GetActorOfClass(GetWorld(), m_TargetClass);
	}
}

FCameraConfiguration ADollyView::GetConfiguration() const
{
	if (m_Target == nullptr || m_Rail == nullptr) return FCameraConfiguration();
	
	FCameraConfiguration CameraConfiguration = FCameraConfiguration();
	CameraConfiguration.SetLocation(m_Rail->GetClosestRailLocation(m_Target->GetActorLocation()));
	CameraConfiguration.SetRotation(UKismetMathLibrary::FindLookAtRotation(CameraConfiguration.GetLocation(), m_Target->GetActorLocation()));
	
	return CameraConfiguration;
}

