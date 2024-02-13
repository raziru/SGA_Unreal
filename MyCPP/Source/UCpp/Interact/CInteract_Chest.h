
#pragma once

#include "CoreMinimal.h"
#include "Interact/CInteract.h"
#include "Inventory/CItem.h"
#include "CInteract_Chest.generated.h"



UCLASS()
class UCPP_API ACInteract_Chest : public ACInteract
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleDefaultsOnly)
		class UCPickupComponent* Pickup;
public:
	ACInteract_Chest();

	virtual void Interact(class AActor* InOther) override;
};
