// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraController.h"

#include "Camera/CameraActor.h"
#include "Camera/CameraSubsystemSettings.h"
#include "Camera/Views/View.h"

void UCameraController::Initialize(ACameraActor* InCamera, const TActorRange<AView>& InViews)
{
	m_CameraSubsystemSettings = GetDefault<UCameraSubsystemSettings>();
	
	m_Camera = InCamera;

	for (AView* View : InViews)
	{
		View->ActivationStateChanged.AddDynamic(this, &UCameraController::OnViewActivationStateChanged);
	}
}

void UCameraController::Start()
{
	m_TargetConfiguration = ComputeAverageConfiguration();
	m_CurrentConfiguration = m_TargetConfiguration;
	ApplyCurrentConfiguration();
}

void UCameraController::Update(float DeltaTime)
{
	m_TargetConfiguration = ComputeAverageConfiguration();
	LerpCurrentConfiguration(DeltaTime);
	ApplyCurrentConfiguration();
}

void UCameraController::OnViewActivationStateChanged(AView* InView, bool InIsActive)
{
	if (InIsActive)
	{
		AddActiveView(InView);
	}else
	{
		RemoveActiveView(InView);
	}
}

void UCameraController::AddActiveView(AView* InView)
{
	m_ActiveViews.AddUnique(InView);
}

void UCameraController::RemoveActiveView(AView* InView)
{
	m_ActiveViews.Remove(InView);
}

FCameraConfiguration UCameraController::ComputeAverageConfiguration() const
{
	FCameraConfiguration AverageConfiguration = FCameraConfiguration();

	if (m_ActiveViews.Num() == 0) return AverageConfiguration;

	float WeightSum = 0;
	FVector2f YawVectorSum = FVector2f::ZeroVector;

	
	for (AView* View : m_ActiveViews)
	{
		float ViewWeight = View->GetWeight();
		if (ViewWeight == 0) continue;

		FCameraConfiguration ViewConfiguration = View->GetConfiguration();

		AverageConfiguration.Pitch += ViewConfiguration.Pitch * ViewWeight;
		AverageConfiguration.Roll += ViewConfiguration.Roll * ViewWeight;

		YawVectorSum += FVector2f(FMath::Cos(FMath::DegreesToRadians(ViewConfiguration.Yaw)), FMath::Sin(FMath::DegreesToRadians(ViewConfiguration.Yaw))) * ViewWeight;

		AverageConfiguration.Pivot += ViewConfiguration.Pivot * ViewWeight;
		AverageConfiguration.FoV += ViewConfiguration.FoV * ViewWeight;
		
		WeightSum += ViewWeight;
	}

	if (WeightSum <= 0) WeightSum = 1;

	AverageConfiguration.Pitch /= WeightSum;
	AverageConfiguration.Roll /= WeightSum;

	YawVectorSum /= WeightSum;
	AverageConfiguration.Yaw  = FMath::RadiansToDegrees(FMath::Atan2(YawVectorSum.Y, YawVectorSum.X));
	
	AverageConfiguration.Pivot /= WeightSum;
	AverageConfiguration.FoV /= WeightSum;
	
	return AverageConfiguration;
}

void UCameraController::LerpCurrentConfiguration(float DeltaTime)
{
	float CameraSpeed = m_CameraSubsystemSettings->CameraSpeed;
	
	if (CameraSpeed == 0)
	{
		m_CurrentConfiguration = m_TargetConfiguration;
		return;
	}
	
	FVector2f CurrentYawVector = FVector2f(FMath::Cos(FMath::DegreesToRadians(m_CurrentConfiguration.Yaw)), FMath::Sin(FMath::DegreesToRadians(m_CurrentConfiguration.Yaw)));
	FVector2f TargetYawVector = FVector2f(FMath::Cos(FMath::DegreesToRadians(m_TargetConfiguration.Yaw)), FMath::Sin(FMath::DegreesToRadians(m_TargetConfiguration.Yaw)));

	CurrentYawVector += (TargetYawVector - CurrentYawVector) * DeltaTime * CameraSpeed;
	m_CurrentConfiguration.Yaw = FMath::RadiansToDegrees(FMath::Atan2(CurrentYawVector.Y, CurrentYawVector.X));

	m_CurrentConfiguration.Pitch += (m_TargetConfiguration.Pitch - m_CurrentConfiguration.Pitch) * DeltaTime * CameraSpeed;
	m_CurrentConfiguration.Roll += (m_TargetConfiguration.Roll - m_CurrentConfiguration.Roll) * DeltaTime * CameraSpeed;
	
	m_CurrentConfiguration.Pivot += (m_TargetConfiguration.Pivot - m_CurrentConfiguration.Pivot) * DeltaTime * CameraSpeed;
	m_CurrentConfiguration.FoV += (m_TargetConfiguration.FoV - m_CurrentConfiguration.FoV) * DeltaTime * CameraSpeed;
}

void UCameraController::ApplyCurrentConfiguration() const
{
	if (m_Camera == nullptr) return;

	m_Camera->SetActorLocation(m_CurrentConfiguration.GetLocation());
	m_Camera->SetActorRotation(m_CurrentConfiguration.GetRotation());
	//TODO set FoV
}
