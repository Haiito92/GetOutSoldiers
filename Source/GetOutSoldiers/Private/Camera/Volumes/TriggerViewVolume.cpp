// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/Volumes/TriggerViewVolume.h"

#include "Components/BoxComponent.h"


// Sets default values
ATriggerViewVolume::ATriggerViewVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_Collider = CreateDefaultSubobject<UBoxComponent>("Collider");

	m_Collider->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	m_Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	
	m_Collider->OnComponentBeginOverlap.AddDynamic(this, &ATriggerViewVolume::OnColliderBeginOverlap);
	m_Collider->OnComponentEndOverlap.AddDynamic(this, &ATriggerViewVolume::OnColliderEndOverlap);
}

void ATriggerViewVolume::OnColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (m_TargetType == ETriggerViewVolumeTargetType::Actor && m_Target != nullptr && OtherActor == m_Target)
	{
		m_TargetCount ++;

		

		if (m_TargetCount == 1)
		{
			SetActive(true);
		}
	}
	else if (m_TargetType == ETriggerViewVolumeTargetType::Class && OtherActor->GetClass() == m_TargetClass)
	{
		m_TargetCount ++;

		
		if (m_TargetCount == 1)
		{
			SetActive(true);
		}
	}
}

void ATriggerViewVolume::OnColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (m_TargetType == ETriggerViewVolumeTargetType::Actor && m_Target != nullptr && OtherActor == m_Target)
	{
		m_TargetCount --;

		if (m_TargetCount == 0)
		{
			SetActive(false);
		}
	}
	else if (m_TargetType == ETriggerViewVolumeTargetType::Class && OtherActor->GetClass() == m_TargetClass)
	{
		m_TargetCount --;
		
		if (m_TargetCount == 0)
		{
			SetActive(false);
		}
	}
}

