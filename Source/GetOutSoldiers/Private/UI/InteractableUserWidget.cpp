// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InteractableUserWidget.h"

bool UInteractableUserWidget::HandleMenuAction(EMenuAction Action)
{
	if (InnerFocusableWidgets.Num() > 0)
	{
		if (InnerFocusableWidgets[currentInnerFocusIndex]->HandleMenuAction(Action)) return true;
	}
	return ReceiveHandleMenuAction(Action);
}

void UInteractableUserWidget::OnWidgetFocusChanged(bool bIsFocused)
{
	ReceiveOnWidgetFocusChanged(bIsFocused);
}

void UInteractableUserWidget::ChangeInnerFocusedWidget(bool bIncrement)
{
	if (InnerFocusableWidgets.Num() != 0)
	{
		InnerFocusableWidgets[currentInnerFocusIndex]->OnWidgetFocusChanged(false);
		currentInnerFocusIndex += bIncrement? 1 : -1;
		if (currentInnerFocusIndex < 0) currentInnerFocusIndex = InnerFocusableWidgets.Num() - 1;
		if (currentInnerFocusIndex >= InnerFocusableWidgets.Num()) currentInnerFocusIndex = 0;
		InnerFocusableWidgets[currentInnerFocusIndex]->SetFocus();
		InnerFocusableWidgets[currentInnerFocusIndex]->OnWidgetFocusChanged(true);
	}
}

bool UInteractableUserWidget::ReceiveHandleMenuAction_Implementation(EMenuAction Action)
{
	return false;
}
