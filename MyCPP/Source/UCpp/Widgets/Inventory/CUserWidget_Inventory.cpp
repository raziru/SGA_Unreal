// Fill out your copyright notice in the Description page of Project Settings.


#include "CUserWidget_Inventory.h"
#include "Global.h"
#include "Components/UniformGridPanel.h"
#include "CUserWidget_ItemButton.h"

void UCUserWidget_Inventory::BuildInventory(const TArray<FItemData>& Inventory, int MaxInventorySize, int ColumnSize)
{
	for (INT i = 0; i < MaxInventorySize; i++)
	{
		int Column = i % ColumnSize;
		int Row = i / ColumnSize;
		UCUserWidget_ItemButton* ItemButton = Cast<UCUserWidget_ItemButton>(CreateWidget(GetWorld(),ItemButtonWidgetClass));
		if (i<Inventory.Num())// && Inventory[i].ItemType == EItemType::Weapon)
		{
			
			ItemButton->MakeItemButton(Inventory[i]);
			ItemButton->Clicked.AddDynamic(this, &UCUserWidget_Inventory::OnClicked);
			ItemButton->RightClicked.AddDynamic(this, &UCUserWidget_Inventory::OnRightClicked);
			
		}
		else
		{
			ItemButton->MakeEmptyButton();

		}
		InventoryPanel->AddChildToUniformGrid(ItemButton, Row, Column);
	}
}

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




