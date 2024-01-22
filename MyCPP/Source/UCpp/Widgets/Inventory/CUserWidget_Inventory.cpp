
#include "CUserWidget_Inventory.h"
#include "Global.h"
#include "Components/UniformGridPanel.h"
#include "CUserWidget_ItemButton.h"

void UCUserWidget_Inventory::SetInventoryType(EInventoryType NewInventoryType)
{
	this->InventoryType = NewInventoryType; 

	switch (InventoryType)
	{
	case EInventoryType::Main:
		UpdateInventoryName("Main");
		break;
	case EInventoryType::Weapon:
		UpdateInventoryName("Weapon");
		break;
	case EInventoryType::Armor:
		UpdateInventoryName("Armor");
		break;
	case EInventoryType::Tool:
		UpdateInventoryName("Tool");
		break;
	case EInventoryType::Consumable:
		UpdateInventoryName("Consumable");
		break;
	case EInventoryType::Max:
		break;
	default:
		break;
	}
}

void UCUserWidget_Inventory::BuildInventory(const TArray<FItemData>& Inventory, int MaxInventorySize, int ColumnSize)
{
	for (INT i = 0; i < MaxInventorySize; i++)
	{
		int Column = i % ColumnSize;
		int Row = i / ColumnSize;
		UCUserWidget_ItemButton* ItemButton = Cast<UCUserWidget_ItemButton>(CreateWidget(GetWorld(),ItemButtonWidgetClass));
		ItemButton->MakeEmptyButton();
		InventoryPanel->AddChildToUniformGrid(ItemButton, Row, Column);
	}
	int index = 0;

	for (FItemData item: Inventory)
	{
		UCUserWidget_ItemButton* ItemButton = Cast<UCUserWidget_ItemButton>(InventoryPanel->GetAllChildren()[index]);
		switch (InventoryType)
		{
		case EInventoryType::Main:
			break;
		case EInventoryType::Weapon:
			if (item.ItemType != EItemType::Weapon)
				continue;
			
			break;
		case EInventoryType::Armor:
			if (item.ItemType != EItemType::Armor)
				continue;
			
			break;
		case EInventoryType::Tool:
			if (item.ItemType != EItemType::Tool)
				continue;
			
			break;
		case EInventoryType::Consumable:
			if (item.ItemType != EItemType::Consumable)
				continue;
			
			break;
		case EInventoryType::Max:
			break;
		default:
			break;
		}

		ItemButton->MakeItemButton(item);
		ItemButton->Clicked.AddDynamic(this, &UCUserWidget_Inventory::OnClicked);
		ItemButton->RightClicked.AddDynamic(this, &UCUserWidget_Inventory::OnRightClicked);	
		
		index++;
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

void UCUserWidget_Inventory::OnPrevInventory()
{
	if (PrevInventory.IsBound())
	{
		PrevInventory.Broadcast();
	}
}

void UCUserWidget_Inventory::OnNextInventory()
{
	if (NextInventory.IsBound())
	{
		NextInventory.Broadcast();
	}
}




