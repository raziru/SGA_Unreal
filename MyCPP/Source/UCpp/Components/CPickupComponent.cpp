

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
	/*for (ACItem* item : Items)
	{
		Inventory->Pickup(item);
	}*/

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
}

void UCPickupComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
}



