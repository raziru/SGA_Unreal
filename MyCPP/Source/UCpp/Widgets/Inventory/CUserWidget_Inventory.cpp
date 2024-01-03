// Fill out your copyright notice in the Description page of Project Settings.


#include "CUserWidget_Inventory.h"
#include "Global.h"
#include "Components/UniformGridPanel.h"
#include "CUserWidget_ItemButton.h"

void UCUserWidget_Inventory::ClearInventory()
{
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

void UCUserWidget_Inventory::OnSelected(FItemData Item)
{
	if (ItemSelected.IsBound())
	{
		ItemSelected.Broadcast(Item);
	}
}




