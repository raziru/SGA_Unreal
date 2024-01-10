// Fill out your copyright notice in the Description page of Project Settings.


#include "CUserWidget_ItemButton.h"
#include "Global.h"
#include "Brushes/SlateImageBrush.h"

void UCUserWidget_ItemButton::ButtonClicked(const FItemData Item)
{
	if (Clicked.IsBound())
	{
		Clicked.Broadcast(Item);
	}
	CLog::Print("Left");

}

void UCUserWidget_ItemButton::ButtonRightClicked(const FItemData Item)
{
	if (RightClicked.IsBound())
	{
		RightClicked.Broadcast(Item);
	}
	CLog::Print("Right");
}
