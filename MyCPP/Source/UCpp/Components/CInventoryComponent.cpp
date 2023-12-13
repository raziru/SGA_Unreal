

#include "CInventoryComponent.h"
#include "Global.h"
#include "Inventory/CInventory.h"
#include "Engine/Texture2D.h"


UCInventoryComponent::UCInventoryComponent()
{
	
}


void UCInventoryComponent::OpenInventory()
{
	//AllinOne Inventory
	for (ACItem* Item : Inventory)
	{
		Item->ShowData();
	}

}

void UCInventoryComponent::PickUp(ACItem* InItem)
{
	InItem->ShowData();
	for (ACItem* Item: Inventory)
	{
		if (Item->GetItemData().ItemName == InItem->GetItemData().ItemName)
		{
			CLog::Log("Same Item");

			if (Item->GetItemData().CurrentStack== Item->GetItemData().MaxStack)
			{
				CLog::Log("Count Over");
				return;
			}
			Item->GetItemData().CurrentStack++;
			return;

		}
	}
	Inventory.Add(InItem);


}

// Called when the game starts
void UCInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}




