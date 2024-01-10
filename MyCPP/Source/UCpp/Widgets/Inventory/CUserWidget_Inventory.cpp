// Fill out your copyright notice in the Description page of Project Settings.


#include "CUserWidget_Inventory.h"
#include "Global.h"
#include "Components/UniformGridPanel.h"
#include "CUserWidget_ItemButton.h"

void UCUserWidget_Inventory::ClearInventory()
{
	if (InventoryPanel->GetAllChildren().Num()<=0)
	{
		return;
	}
	for (UWidget* widget : InventoryPanel->GetAllChildren())
	{
		widget->RemoveFromParent();
	}
	InventoryPanel->ClearChildren();

}

void UCUserWidget_Inventory::RefreshInventory(const TArray<FItemData>& Inventory, int MaxInventorySize, int ColumnSize)
{
	ClearInventory();
	BuildInventory(Inventory, MaxInventorySize, ColumnSize);
}

void UCUserWidget_Inventory::OnClicked(FItemData Item)
{
	if (ItemClicked.IsBound())
	{
		ItemClicked.Broadcast(Item);
	}
}

void UCUserWidget_Inventory::OnRightClicked(FItemData Item)
{
	if (ItemRightClicked.IsBound())
	{
		ItemRightClicked.Broadcast(Item);
	}
}





