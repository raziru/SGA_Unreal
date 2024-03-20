

#include "Components/CPickupComponent.h"
#include "Global.h"
#include "Components/CInventoryComponent.h"
#include "Inventory/CItem.h"


UCPickupComponent::UCPickupComponent()
{

}


void UCPickupComponent::Pickup(AActor* InOther)
{
	UCInventoryComponent* Inventory = CHelpers::GetComponent<UCInventoryComponent>(InOther);
	CheckNull(Inventory);
	
	CheckTrue(IsOpened);

	for (TPair<UClass*, int> ItemClass: ItemClasses)
	{
		ACItem* item = Cast<ACItem>(GetOwner()->GetWorld()->SpawnActor(ItemClass.Key));
		if (!!item)
		{
			for (int i = 0; i < ItemClass.Value; i++)
			{
				Inventory->Pickup(item);
			}
		}
		item->Destroy();
	}
	IsOpened = true;
}

void UCPickupComponent::BeginPlay()
{
	Super::BeginPlay();

	CheckNull(DataTable);

	TArray< FItemTableData*> datas;
	DataTable->GetAllRows<FItemTableData>("", datas);


	if (IsRand)
	{
		for (FItemTableData* data : datas)
		{
			if (FMath::RandRange(0.0f, 1.0f) >= 0.5f)
			{
				TPair<TSubclassOf<class ACItem>, int> ItemData;
				ItemData.Key = data->item;
				ItemData.Value = FMath::RandRange(1, 4);
				ItemClasses.Add(ItemData);
			}

		};
	}
	else
	{
		for (FItemTableData* data : datas)
		{
			
			TPair<TSubclassOf<class ACItem>, int> ItemData;
			ItemData.Key = data->item;
			ItemData.Value = data->Count;
			ItemClasses.Add(ItemData);		

		};
	}
	
	
	
}



