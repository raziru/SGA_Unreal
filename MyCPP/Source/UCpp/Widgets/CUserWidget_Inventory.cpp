// Fill out your copyright notice in the Description page of Project Settings.


#include "CUserWidget_Inventory.h"
#include "Global.h"
#include "Inventory/CItem.h"
#include "Components/UniformGridPanel.h"
#include "CUserWidget_ItemButton.h"

//void UCUserWidget_Inventory::BuildInventory(const TArray<class ACItem*>& Inventory, int MaxInventorySize, int ColumnSize)
//{
//	for (int i = 0; i < MaxInventorySize; i++)
//	{
//		CheckNull(ItemButtonWidgetClass);
//
//		ItemButtonWidget = Cast<UCUserWidget_ItemButton>(CreateWidget(this, ItemButtonWidgetClass));
//		CheckNull(ItemButtonWidget);
//
//		if (i < Inventory.Num())
//		{
//			ItemButtonWidget->SetItem(Inventory[i]);
//		}
//		else
//		{
//			ItemButtonWidget->SetItem(NULL);
//		}
//		InventoryPanel->AddChildToUniformGrid(ItemButtonWidget, i / ColumnSize, i % ColumnSize);
//	}
//}
//
void UCUserWidget_Inventory::ClearInventory()
{
	for (UWidget* widget : InventoryPanel->GetAllChildren())
	{
		widget->RemoveFromParent();
	}
	InventoryPanel->ClearChildren();

}

void UCUserWidget_Inventory::RefreshInventory(const TArray<class ACItem*>& Inventory, int MaxInventorySize, int ColumnSize)
{
	ClearInventory();
	BuildInventory(Inventory, MaxInventorySize, ColumnSize);
}




