// Fill out your copyright notice in the Description page of Project Settings.


#include "CUserWidget_ItemButton.h"
#include "Global.h"
#include "Brushes/SlateImageBrush.h"

void UCUserWidget_ItemButton::ButtonClicked(const FItemData Item)
{
	if (OnSelected.IsBound())
	{
		OnSelected.Broadcast(Item);
	}

}
