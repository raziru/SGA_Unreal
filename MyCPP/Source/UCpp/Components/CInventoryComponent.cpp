

#include "CInventoryComponent.h"
#include "Global.h"
#include "Widgets/Inventory/CUserWidget_Inventory.h"

UCInventoryComponent::UCInventoryComponent()
{


}

void UCInventoryComponent::OpenInventory()
{
	if (!IsInventoryOpened)
	{
		if (IsMagicInventoryOpened)
		{
			OpenMagicInventory(EInventoryType::Weapon);
		}
		OpenInventory(InventoryType);
	}
	else
	{
		OpenInventory(InventoryType);
	}
}

void UCInventoryComponent::OpenMagicInventory()
{
	if (!IsMagicInventoryOpened)
	{
		if (IsInventoryOpened)
		{
			OpenInventory(InventoryType);
		}
		OpenMagicInventory(EInventoryType::Weapon);

	}
	else
	{
		OpenMagicInventory(EInventoryType::Weapon);

	}
}
void UCInventoryComponent::OnClicked(FItemData NewItem)
{
	CheckFalse(CanChange);
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
		FTransform transform;
		Consumable = GetOwner()->GetWorld()->SpawnActorDeferred<ACItem_Consumable>(NewItem.ItemClass, transform, GetOwner());
		UGameplayStatics::FinishSpawningActor(Consumable, transform);
		CheckNull(Consumable);
		CLog::Print("Consumable Success");
		Consumable->ConsumableEvent();
		IsConsumable = true;
		ChangedItem = NewItem;
		if (!!Consumable->GetData())
		{
			if (SetNewConsumable.IsBound())
			{
				SetNewConsumable.Broadcast(Consumable->GetData());
			}
		}	
		else
		{
			DecreaseCount(ChangedItem);
		}
		
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
	ACItem_Weapon* WeaponItem;
	ACItem_Armor* ArmorItem;
	ACItem_Consumable* Consumable;
	switch (NewItem.ItemType)
	{
	case EItemType::Weapon:
		WeaponItem = Cast<ACItem_Weapon>(item);
		if (DropMainWeapon.IsBound())
		{
			DropMainWeapon.Broadcast(WeaponItem->GetData(),WeaponItem->GetType());
		}
		break;
	case EItemType::Armor:
		ArmorItem = Cast<ACItem_Armor>(item);
		if (DropArmor.IsBound())
		{
			DropArmor.Broadcast(ArmorItem->GetClass());
		}
		break;
	case EItemType::Tool:
		break;
	case EItemType::Consumable:
		Consumable = Cast<ACItem_Consumable>(item);
		if (DropConsumable.IsBound())
		{
			DropConsumable.Broadcast(Consumable->GetData());
		}
		break;
	case EItemType::Max:
		break;
	default:
		break;
	}

	UGameplayStatics::FinishSpawningActor(item, transform);
}

void UCInventoryComponent::NextInventory()
{
	switch (InventoryType)
	{
	case EInventoryType::Main:
		InventoryType = EInventoryType::Weapon;
		break;
	case EInventoryType::Weapon:
		InventoryType = EInventoryType::Armor;
		break;
	case EInventoryType::Armor:
		InventoryType = EInventoryType::Tool;
		break;
	case EInventoryType::Tool:
		InventoryType = EInventoryType::Consumable;
		break;
	case EInventoryType::Consumable:
		InventoryType = EInventoryType::Main;
		break;
	case EInventoryType::Max:
		break;
	default:
		break;
	}
	InventoryWidget->SetInventoryType(InventoryType);
	InventoryWidget->RefreshInventory(Inventory, MaxInventorySize, ColumnSize);
}

void UCInventoryComponent::PrevInventory()
{
	switch (InventoryType)
	{
	case EInventoryType::Main:
		InventoryType = EInventoryType::Consumable;
		break;
	case EInventoryType::Weapon:
		InventoryType = EInventoryType::Main;
		break;
	case EInventoryType::Armor:
		InventoryType = EInventoryType::Weapon;
		break;
	case EInventoryType::Tool:
		InventoryType = EInventoryType::Armor;
		break;
	case EInventoryType::Consumable:
		InventoryType = EInventoryType::Tool;
		break;
	case EInventoryType::Max:
		break;
	default:
		break;
	}
	InventoryWidget->SetInventoryType(InventoryType);
	InventoryWidget->RefreshInventory(Inventory, MaxInventorySize, ColumnSize);

}

// Called when the game starts
void UCInventoryComponent::BeginPlay()
{
	Super::BeginPlay();	
}


void UCInventoryComponent::OpenInventory(EInventoryType NewInventoryType)
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
			/*TSubclassOf<UCUserWidget_Inventory>InventoryClass;
			CHelpers::GetClass<UCUserWidget_Inventory>(&InventoryClass, "WidgetBlueprint'/Game/Widgets/Inventory/WB_Inventory.WB_Inventory_C''");*/
			InventoryWidget = Cast<UCUserWidget_Inventory>(CreateWidget(GetWorld(), InventoryWidgetClass));
			CheckNull(InventoryWidget);
			InventoryWidget->SetInventoryType(NewInventoryType);
			InventoryWidget->BuildInventory(Inventory, MaxInventorySize, ColumnSize);
			InventoryWidget->AddToViewport();
		}		
		else
		{
			InventoryWidget->SetInventoryType(NewInventoryType);
			InventoryWidget->ClearInventory();
			InventoryWidget->BuildInventory(Inventory, MaxInventorySize, ColumnSize);
			InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		}
		//CLog::Print(Inventory.Num());

		CheckNull(InventoryWidget);

		InventoryWidget->ItemClicked.AddDynamic(this, &UCInventoryComponent::OnClicked);
		InventoryWidget->ItemRightClicked.AddDynamic(this, &UCInventoryComponent::OnRightClicked);
		InventoryWidget->NextInventory.AddDynamic(this, &UCInventoryComponent::NextInventory);
		InventoryWidget->PrevInventory.AddDynamic(this, &UCInventoryComponent::PrevInventory);

		//OnSelected.AddDynamic

	}
	else
	{
		CheckNull(InventoryWidget);
		//InventoryWidget->ClearInventory();
		//InventoryWidget->RemoveFromParent();
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		InventoryWidget->ItemClicked.Clear();
		InventoryWidget->ItemRightClicked.Clear();
	}
	IsInventoryOpened = !IsInventoryOpened;
}




void UCInventoryComponent::OpenMagicInventory(EInventoryType NewInventoryType)
{
	//AllinOne Inventory
	for (FItemData Item : MagicInventory)
	{
		Item.ShowData();
	}


	if (!IsMagicInventoryOpened)
	{
		CheckNull(MagicInventoryWidgetClass);
		if (!!!MagicInventoryWidget)
		{
			MagicInventoryWidget = Cast<UCUserWidget_Inventory>(CreateWidget(GetWorld(), MagicInventoryWidgetClass));
			CheckNull(MagicInventoryWidget);
			MagicInventoryWidget->SetInventoryType( NewInventoryType);
			MagicInventoryWidget->BuildInventory(MagicInventory, MaxInventorySize, ColumnSize);
			MagicInventoryWidget->AddToViewport();

		}
		else
		{
			MagicInventoryWidget->SetInventoryType(NewInventoryType);
			MagicInventoryWidget->ClearInventory();
			MagicInventoryWidget->BuildInventory(MagicInventory, MaxInventorySize, ColumnSize);
			//MagicInventoryWidget->AddToViewport();
			MagicInventoryWidget->SetVisibility(ESlateVisibility::Visible);

		}
		//CLog::Print(Inventory.Num());

		CheckNull(MagicInventoryWidget);

		MagicInventoryWidget->ItemClicked.AddDynamic(this, &UCInventoryComponent::OnClicked);
		//MagicInventoryWidget->ItemRightClicked.AddDynamic(this, &UCInventoryComponent::OnRightClicked);
		//MagicInventoryWidget->NextInventory.AddDynamic(this, &UCInventoryComponent::NextInventory);
		//MagicInventoryWidget->PrevInventory.AddDynamic(this, &UCInventoryComponent::PrevInventory);

		//OnSelected.AddDynamic

		
	}
	else
	{
		CheckNull(MagicInventoryWidget);
		//MagicInventoryWidget->ClearInventory();
//`		MagicInventoryWidget->RemoveFromParent();
		MagicInventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		
		MagicInventoryWidget->ItemClicked.Clear();
		MagicInventoryWidget->ItemRightClicked.Clear();
	}
	IsMagicInventoryOpened = !IsMagicInventoryOpened;
}
void UCInventoryComponent::Pickup(ACItem* InItem)
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

void UCInventoryComponent::PickupMagic(ACItem* InItem)
{
	InItem->ShowData();

	FItemData CopyItem;
	CopyItem = InItem->GetItemData();
	bool IsExist = false;
	int index = 0;
	for (FItemData data : MagicInventory)
	{
		if (data.ItemName == CopyItem.ItemName)
		{
			CLog::Log("Same Item");

			return;
		}
		index++;
	}

	if (!IsExist)
	{
		CopyItem.ItemIndex = MagicInventory.Num();
		MagicInventory.Add(CopyItem);
	}
	if (IsMagicInventoryOpened)
	{
		CheckNull(InventoryWidget);
		InventoryWidget->RefreshInventory(MagicInventory, MaxInventorySize, ColumnSize);
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
		break;
	case EItemType::Max:
		break;
	default:
		break;
	}
	
}

void UCInventoryComponent::EndConsumableAction()
{
	DecreaseCount(ChangedItem);
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
				
				Inventory.RemoveAt(i);//Remove보다 at으로 인덱스로 접근하는 것이 에러가 발생하지않는다.
				//Inventory.Remove(Inventory[i])//포인터를 없애기 때문에 
				//RemoveAt indeed would solve this problem (in fact it much faster), also not using pointer is good solution, you could use varable that you copied which would naturally have diffrent memoery address then array.
			}
			if (IsInventoryOpened)
			{
				CheckNull(InventoryWidget);
				InventoryWidget->RefreshInventory(Inventory, MaxInventorySize, ColumnSize);
			}
			break;
		}
	}
}






