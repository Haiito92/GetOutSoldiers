// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InteractableUserWidget.h"

bool UInteractableUserWidget::HandleMenuAction(EMenuAction Action)
{
	if (InnerFocusableWidgets.Num() > currentInnerFocusIndex)
	{
		if (InnerFocusableWidgets[currentInnerFocusIndex]->HandleMenuAction(Action)) return true;
	}
	return ReceiveHandleMenuAction(Action);
}

bool UInteractableUserWidget::HandleMenuActionReleased(EMenuAction Action)
{
	if (InnerFocusableWidgets.Num() > currentInnerFocusIndex)
	{
		if (InnerFocusableWidgets[currentInnerFocusIndex]->HandleMenuActionReleased(Action)) return true;
	}
	return ReceiveHandleMenuActionReleased(Action);
}

void UInteractableUserWidget::OnWidgetFocusChanged(bool bIsFocused)
{
	if (InnerFocusableWidgets.Num() > currentInnerFocusIndex)
	{
		InnerFocusableWidgets[currentInnerFocusIndex]->OnWidgetFocusChanged(bIsFocused);
	}
	ReceiveOnWidgetFocusChanged(bIsFocused);
}

void UInteractableUserWidget::ChangeInnerFocusedWidget(bool bIncrement)
{
	if (InnerFocusableWidgets.Num() != 0)
	{
		InnerFocusableWidgets[currentInnerFocusIndex]->OnWidgetFocusChanged(false);
		currentInnerFocusIndex += bIncrement? 1 : -1;
		if (bLoopOnChangeIndex)
		{
			if (currentInnerFocusIndex < 0) currentInnerFocusIndex = InnerFocusableWidgets.Num() - 1;
			if (currentInnerFocusIndex >= InnerFocusableWidgets.Num()) currentInnerFocusIndex = 0;
		}
		else
		{
			currentInnerFocusIndex = FMath::Clamp(currentInnerFocusIndex, 0, InnerFocusableWidgets.Num() - 1);
		}
		InnerFocusableWidgets[currentInnerFocusIndex]->OnWidgetFocusChanged(true);
	}
}

bool UInteractableUserWidget::ReceiveHandleMenuAction_Implementation(EMenuAction Action)
{
	return false;
}

bool UInteractableUserWidget::ReceiveHandleMenuActionReleased_Implementation(EMenuAction Action)
{
	return false;
}
