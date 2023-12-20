

#include "CInventoryComponent.h"
#include "Global.h"
#include "Widgets/CUserWidget_Inventory.h"

UCInventoryComponent::UCInventoryComponent()
{


}

void UCInventoryComponent::OnSelected(const FItemData NewItem)
{
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


	//ACItem* NewItem = NewObject<ACItem>();
	
	FItemData CopyItem;
	CopyItem = SetData(InItem);
	CopyItem.SetData(InItem->GetItemData());
	//SetData(CopyItem)
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

FItemData UCInventoryComponent::SetData(ACItem* InItem)
{
	FItemData_Weapon NewItem;
	NewItem.ItemType = InItem->GetItemData().ItemType;
	NewItem.ItemName = InItem->GetItemData().ItemName;
	NewItem.ItemDescription = InItem->GetItemData().ItemDescription;
	NewItem.ItemImage = InItem->GetItemData().ItemImage;
	NewItem.CurrentStack = InItem->GetItemData().CurrentStack;
	NewItem.MaxStack = InItem->GetItemData().MaxStack;
	NewItem.ItemIndex = InItem->GetItemData().ItemIndex;
	return NewItem;

	switch (InItem->GetItemData().ItemType)
	{
	case EItemType::Weapon :
		
		break;

	case EItemType::Armor:
		break;

	case EItemType::Tool:
		break;

	case EItemType::Consumable:
		break;
	}
	

	

}







