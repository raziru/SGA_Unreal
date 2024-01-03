

#include "CInventoryComponent.h"
#include "Global.h"
#include "Widgets/Inventory/CUserWidget_Inventory.h"

UCInventoryComponent::UCInventoryComponent()
{


}

void UCInventoryComponent::OnSelected(const FItemData NewItem)
{
	ACItem_Weapon* WeaponItem;
	ACItem_Armor* ArmorItem;
	switch (NewItem.ItemType)
	{
	case EItemType::Weapon:
		CLog::Print("Check");
		WeaponItem = Cast<ACItem_Weapon>(GetWorld()->SpawnActor(NewItem.ItemClass));
		CheckNull(WeaponItem);
		CLog::Print("Weapon Success");
		CLog::Print((int32)WeaponItem->GetType());
		if (SetNewAction.IsBound())
		{
			SetNewAction.Broadcast(WeaponItem->GetData(), WeaponItem->GetType());
		}
		WeaponItem->Destroy();
		break;
	case EItemType::Armor:
		CLog::Print("Check");
		ArmorItem = Cast<ACItem_Armor>(GetWorld()->SpawnActor(NewItem.ItemClass));
		CheckNull(ArmorItem);
		CLog::Print("Armor Success");
		if (SetNewArmor.IsBound())
		{
			SetNewArmor.Broadcast(ArmorItem->GetArmorClass());
		}
		ArmorItem->Destroy();
		break;
	case EItemType::Consumable:
		CLog::Print("Check");
		break;
	}
	if (SetNewItem.IsBound())
	{
		SetNewItem.Broadcast(NewItem);
	}
	//CLog::Log(Item.);
}

// Called when the game starts
void UCInventoryComponent::BeginPlay()
{
	Super::BeginPlay();	
}


void UCInventoryComponent::OpenInventory()
{
	//AllinOne Inventory
	for (FItemData Item : Inventory)
	{
		Item.ShowData();
	}


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
			InventoryWidget->ClearInventory();
			InventoryWidget->BuildInventory(Inventory, MaxInventorySize, ColumnSize);
			InventoryWidget->AddToViewport();
		}
		//CLog::Print(Inventory.Num());

		CheckNull(InventoryWidget);

		InventoryWidget->ItemSelected.AddDynamic(this, &UCInventoryComponent::OnSelected);
		//OnSelected.AddDynamic
	}
	else
	{
		CheckNull(InventoryWidget);
		InventoryWidget->ClearInventory();
		InventoryWidget->RemoveFromParent();
		InventoryWidget->ItemSelected.Clear();
	}
	IsInventoryOpened = !IsInventoryOpened;
}

void UCInventoryComponent::PickUp(ACItem* InItem)
{
	InItem->ShowData();
	
	FItemData CopyItem;
	CopyItem.SetData(InItem->GetItemData());
	bool IsExist = false;
	int index = 0;
	for (FItemData data: Inventory)
	{
		if (data.ItemName == CopyItem.ItemName)
		{
			CLog::Log("Same Item");

			if (data.CurrentStack == data.MaxStack)
			{
				CLog::Log("Count Over");
				return;
			}
			FItemData TempData;
			TempData.SetData(data);
			TempData.CurrentStack += CopyItem.CurrentStack;
			if (TempData.CurrentStack>=TempData.MaxStack)
			{
				TempData.CurrentStack = TempData.MaxStack;
			}
			IsExist = true;
			Inventory[index] = TempData;
			break;
		}
		index++;
	}

	if (!IsExist)
	{
		CopyItem.ItemIndex = Inventory.Num();
		Inventory.Add(CopyItem);
	}
	if (IsInventoryOpened)
	{
		CheckNull(InventoryWidget);
		InventoryWidget->RefreshInventory(Inventory, MaxInventorySize, ColumnSize);
	}

}






