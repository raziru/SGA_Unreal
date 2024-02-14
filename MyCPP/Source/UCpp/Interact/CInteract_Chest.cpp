

#include "Interact/CInteract_Chest.h"
#include "Global.h"
#include "Components/CPickupComponent.h"
ACInteract_Chest::ACInteract_Chest()
{
	CHelpers::CreateActorComponent<UCPickupComponent>(this, &Pickup, "Pickup");

}

void ACInteract_Chest::Interact(AActor* InOther)
{
	Pickup->Pickup(InOther);
	Super::Interact(InOther);
}
