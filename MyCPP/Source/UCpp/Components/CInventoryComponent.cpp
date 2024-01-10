

#include "CInventoryComponent.h"
#include "Global.h"
#include "Widgets/Inventory/CUserWidget_Inventory.h"

UCInventoryComponent::UCInventoryComponent()
{


}

void UCInventoryComponent::OnClicked(FItemData NewItem)
{
	ACItem_Weapon* WeaponItem;
	ACItem_Armor* ArmorItem;
	ACItem_Consumable* Consumable;
	SelectedItemType = NewItem.ItemType;
	switch (SelectedItemType)
	{
	case EItemType::Weapon:
		CLog::Print("Check");
		WeaponItem = Cast<ACItem_Weapon>(GetOwner()->GetWorld()->SpawnActor(NewItem.ItemClass));
		CheckNull(WeaponItem);
		CLog::Print("Weapon Success");
		CLog::Print(GetOwner()->GetName());
		CLog::Print((int32)WeaponItem->GetType());
		if (SetNewMainWeapon.IsBound())
		{
			SetNewMainWeapon.Broadcast(WeaponItem->GetData(), WeaponItem->GetType());
		}
		WeaponItem->Destroy();
		break;
	case EItemType::Armor:
		CLog::Print("Check");
		ArmorItem = Cast<ACItem_Armor>(GetOwner()->GetWorld()->SpawnActor(NewItem.ItemClass));
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
		Consumable = Cast<ACItem_Consumable>(GetOwner()->GetWorld()->SpawnActor(NewItem.ItemClass));
		CheckNull(Consumable);
		
		CLog::Print("Consumable Success");
		if (SetNewTool.IsBound())
		{
			SetNewTool.Broadcast(Consumable->GetData(), true);
		}
		
		IsConsumable = true;
		ChangedItem = NewItem;
		Consumable->Destroy();
		break;
	}
	if (SetNewItem.IsBound())
	{
		SetNewItem.Broadcast(NewItem);
	}	
}

void UCInventoryComponent::OnRightClicked(FItemData NewItem)
{
	DecreaseCount(NewItem);
	FTransform transform;
	FVector Vector = { (float)(rand() % 10 + 5), (float)(rand() % 10 + 5), 0.0f };
	transform.SetLocation(GetOwner()->GetActorLocation() + Vector);

	ACItem* item = GetOwner()->GetWorld()->SpawnActorDeferred<ACItem>(NewItem.ItemClass, transform);
	UGameplayStatics::FinishSpawningActor(item, transform);

	//GetOwner()->GetWorld()->SpawnActor(NewItem.ItemClass,transform.GetRotation(),transform.GetLocation(),GetOwner());

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

		InventoryWidget->ItemClicked.AddDynamic(this, &UCInventoryComponent::OnClicked);
		InventoryWidget->ItemRightClicked.AddDynamic(this, &UCInventoryComponent::OnRightClicked);

		//OnSelected.AddDynamic
	}
	else
	{
		CheckNull(InventoryWidget);
		InventoryWidget->ClearInventory();
		InventoryWidget->RemoveFromParent();
		InventoryWidget->ItemClicked.Clear();
		InventoryWidget->ItemRightClicked.Clear();
	}
	IsInventoryOpened = !IsInventoryOpened;
}

void UCInventoryComponent::PickUp(ACItem* InItem)
{
	InItem->ShowData();
	
	FItemData CopyItem;
	CopyItem = InItem->GetItemData();
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
			TempData = data;
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

void UCInventoryComponent::EndToolAction()
{
	switch (SelectedItemType)
	{
	case EItemType::Weapon:
		break;
	case EItemType::Armor:
		break;
	case EItemType::Tool:
		break;
	case EItemType::Consumable:
		DecreaseCount(ChangedItem);

		break;
	case EItemType::Max:
		break;
	default:
		break;
	}
	/*if (IsConsumable)
	{
		
		
	}*/
	
}

void UCInventoryComponent::DecreaseCount(FItemData NewItem)
{
	for (int i = 0; i < Inventory.Num(); i++)
	{
		if (Inventory[i].ItemClass == NewItem.ItemClass)
		{
			Inventory[i].CurrentStack--;
			if (Inventory[i].CurrentStack == 0)
			{
				Inventory.RemoveAt(i);//Remove���� at���� �ε����� �����ϴ� ���� ������ �߻������ʴ´�.
				//Inventory.Remove(Inventory[i])//�����͸� ���ֱ� ������ 
				//RemoveAt indeed would solve this problem (in fact it much faster), also not using pointer is good solution, you could use varable that you copied which would naturally have diffrent memoery address then array.
			}

			if (IsInventoryOpened)
			{
				CheckNull(InventoryWidget);
				InventoryWidget->RefreshInventory(Inventory, MaxInventorySize, ColumnSize);
			}
		}
	}
}






