// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractableUserWidget.generated.h"

enum EMenuAction : int;
/**
 * 
 */
UCLASS()
class GETOUTSOLDIERS_API UInteractableUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	//Returns true if action was Handled (if not parent will handle it)
	UFUNCTION(BlueprintCallable)
	bool HandleMenuAction(EMenuAction Action);

	//Warn Widget it is currently focused (Used to display selected button for example)
	UFUNCTION(BlueprintCallable)
	void OnWidgetFocusChanged(bool bIsFocused);

protected:
	UFUNCTION(BlueprintImplementableEvent)
    void ReceiveOnWidgetFocusChanged(bool bIsFocused);UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	
	bool ReceiveHandleMenuAction(EMenuAction Action);

	UFUNCTION(BlueprintCallable)
	void ChangeInnerFocusedWidget(bool bIncrement);

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<TObjectPtr<UInteractableUserWidget>> InnerFocusableWidgets;
	
	UPROPERTY(BlueprintReadWrite)
	int currentInnerFocusIndex = 0;
	
	UPROPERTY(EditDefaultsOnly)
	bool bLoopOnChangeIndex = false;
	
};
