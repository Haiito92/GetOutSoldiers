// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ViewVolume.h"
#include "TriggerViewVolume.generated.h"

class UBoxComponent;

UENUM()
enum class ETriggerViewVolumeTargetType : uint8
{
	None = 0,
	Actor = 1,
	Class = 2
};

UCLASS(Blueprintable)
class GETOUTSOLDIERS_API ATriggerViewVolume : public AViewVolume
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATriggerViewVolume();

private:
	UFUNCTION()
	void OnColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
								const FHitResult& SweepResult);
	UFUNCTION()
	void OnColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> m_Collider;

	UPROPERTY(EditAnywhere, DisplayName="TargetType")
	ETriggerViewVolumeTargetType m_TargetType;
	UPROPERTY(EditAnywhere, DisplayName="TargetActor")
	TObjectPtr<AActor> m_Target;
	UPROPERTY(EditAnywhere, DisplayName="TargetClass")
	TSoftClassPtr<AActor> m_TargetClass;
	
	UPROPERTY()
	unsigned int m_TargetCount = 0;
	
};
