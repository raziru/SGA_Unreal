

#include "CInventoryComponent.h"
#include "Global.h"
#include "Inventory/CInventory.h"
#include "Widgets/CUserWidget_Inventory.h"

UCInventoryComponent::UCInventoryComponent()
{


}

// Called when the game starts
void UCInventoryComponent::BeginPlay()
{
	Super::BeginPlay();


}


void UCInventoryComponent::OpenInventory()
{
	//AllinOne Inventory
	/*for (ACItem* Item : Inventory)
	{
		Item->ShowData();
	}*/


	if (!IsInventoryOpened)
	{
		CheckNull(InventoryWidgetClass);
		if (!!!InventoryWidget)
		{
			InventoryWidget = Cast<UCUserWidget_Inventory>(CreateWidget(GetWorld(), InventoryWidgetClass));
			CheckNull(InventoryWidget);
			InventoryWidget->BuildInventory(Inventory, MaxInventorySize, ColumnSize);
			InventoryWidget->AddToViewport();
		}		
		else
		{
			InventoryWidget->BuildInventory(Inventory, MaxInventorySize, ColumnSize);
			//InventoryWidget->AddToViewport();
			InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		}
		CLog::Print(Inventory.Num());

	
		
	}
	else
	{
		CheckNull(InventoryWidget);
		InventoryWidget->ClearInventory();
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		//InventoryWidget->RemoveFromParent();
	}
	IsInventoryOpened = !IsInventoryOpened;
}

void UCInventoryComponent::PickUp(ACItem* InItem)
{
	InItem->ShowData();
	for (ACItem* Item: Inventory)
	{
		if (Item->GetItemData().ItemName == InItem->GetItemData().ItemName)
		{
			CLog::Log("Same Item");

			if (Item->GetItemData().CurrentStack == Item->GetItemData().MaxStack)
			{
				CLog::Log("Count Over");
				return;
			}
			Item->GetItemData().CurrentStack++;
			return;

		}
	}
	Inventory.Add(InItem);

	if (IsInventoryOpened)
	{
		CheckNull(InventoryWidget);
		InventoryWidget->RefreshInventory(Inventory, MaxInventorySize, ColumnSize);
	}


}






