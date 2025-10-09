// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rail.generated.h"

class USplineComponent;

UCLASS(Blueprintable)
class GETOUTSOLDIERS_API ARail : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARail();

	FVector GetClosestRailLocation(const FVector& InWorldLocation) const;
private:
	UPROPERTY(VisibleAnywhere, Category="Rail")
	TObjectPtr<USplineComponent> m_Spline;
};
