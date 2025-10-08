// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/ViewVolumeBlender.h"

#include "Camera/Views/View.h"
#include "Camera/Volumes/ViewVolume.h"

void UViewVolumeBlender::Initialize(const TActorRange<AViewVolume>& ViewVolumes) const
{
	int NextVolumeUId = 0;
	for (AViewVolume* ViewVolume : ViewVolumes)
	{
		ViewVolume->Initialize(NextVolumeUId);

		ViewVolume->ActivationStateChanged.AddDynamic(this, &UViewVolumeBlender::OnVolumeActivationStateChanged);

		ViewVolume->Start();

		NextVolumeUId++;
	}
}

void UViewVolumeBlender::Update(float DeltaTime)
{
	TArray<TObjectPtr<AView>> Views;
	m_VolumesPerView.GetKeys(Views);
	for (AView* View : Views)
	{
		View->SetWeight(0.0f);
	}

	m_ActiveViewVolumes.Sort([](const AViewVolume& A, const AViewVolume& B)
	{
		if (A.GetPriority() > B.GetPriority()) return false;
		if (A.GetPriority() < B.GetPriority()) return true;

		if (A.GetUId() < B.GetUId()) return false;
		if (A.GetUId() > B.GetUId()) return true;
		
		return false;
	});

	for (AViewVolume* ViewVolume : m_ActiveViewVolumes)
	{
		float Weight = FMath::Clamp(ViewVolume->ComputeSelfWeight(), 0.0f, 1.0f);
		float RemainingWeight = 1.0f - Weight;
		for (AView* View : Views)
		{
			View->SetWeight(View->GetWeight() * RemainingWeight);
		}

		ViewVolume->GetView()->SetWeight(ViewVolume->GetView()->GetWeight() + Weight);
	}
}

void UViewVolumeBlender::OnVolumeActivationStateChanged(AViewVolume* InVolume, bool InIsActive)
{
	if (InIsActive)
	{
		AddActiveVolume(InVolume);
	}else
	{
		RemoveActiveVolume(InVolume);
	}
}

void UViewVolumeBlender::AddActiveVolume(AViewVolume* InVolume)
{
	if (m_ActiveViewVolumes.Contains(InVolume)) return;
	m_ActiveViewVolumes.Add(InVolume);

	AView* View = InVolume->GetView();
	if (!m_VolumesPerView.Contains(View))
	{
		View->SetActive(true);

		m_VolumesPerView.Add(View);		
	}

	TArray<TObjectPtr<AViewVolume>>* VolumesOfView = m_VolumesPerView.Find(View);
	if (!VolumesOfView->Contains(InVolume))
	{
		VolumesOfView->Add(InVolume);
	}
}

void UViewVolumeBlender::RemoveActiveVolume(AViewVolume* InVolume)
{
	m_ActiveViewVolumes.Remove(InVolume);
	
	AView* View = InVolume->GetView();

	if (!m_VolumesPerView.Contains(View)) return;

	TArray<TObjectPtr<AViewVolume>>* VolumesOfView = m_VolumesPerView.Find(View);
	VolumesOfView->Remove(InVolume);
	
	if (VolumesOfView->Num() > 0) return;

	View->SetActive(false);
	m_VolumesPerView.Remove(View);
}
