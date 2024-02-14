

#include "Interact/CInteract.h"
#include "Global.h"
#include "GameFramework/Character.h"

// Sets default values
ACInteract::ACInteract()
{

}

void ACInteract::Interact(AActor* InOther)
{
	if (EndInteract.IsBound())
	{
		EndInteract.Broadcast();
	}
}

void ACInteract::BeginPlay()
{
	
	Super::BeginPlay();
	
}


