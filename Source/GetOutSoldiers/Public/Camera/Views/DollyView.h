// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "View.h"
#include "DollyView.generated.h"

class ARail;

UENUM()
enum class EDollyViewTargetType : uint8
{
	None = 0,
	Actor = 1,
	Class = 2
};

UCLASS(Blueprintable)
class GETOUTSOLDIERS_API ADollyView : public AView
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADollyView();

	virtual void StartView() override;
	
	virtual FCameraConfiguration GetConfiguration() const override;
	
private:
	UPROPERTY(EditAnywhere, DisplayName="Rail")
	TObjectPtr<ARail> m_Rail;

	UPROPERTY(EditAnywhere, DisplayName="TargetType")
	EDollyViewTargetType m_TargetType;
	UPROPERTY(EditAnywhere, DisplayName="TargetActor")
	TObjectPtr<AActor> m_Target;
	UPROPERTY(EditAnywhere, DisplayName="TargetClass")
	TSubclassOf<AActor> m_TargetClass;
};
