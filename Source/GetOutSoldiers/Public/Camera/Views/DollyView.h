// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "View.h"
#include "DollyView.generated.h"

class ARail;

UCLASS(Blueprintable)
class GETOUTSOLDIERS_API ADollyView : public AView
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADollyView();

	virtual FCameraConfiguration GetConfiguration() const override;
	
private:
	UPROPERTY(EditAnywhere, DisplayName="Rail")
	TObjectPtr<ARail> m_Rail;
	UPROPERTY(EditAnywhere, DisplayName="Target")
	TObjectPtr<AActor> m_Target;
};
