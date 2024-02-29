

#include "Interact/CInteract_Teleport.h"

void ACInteract_Teleport::Interact(AActor* InOther)
{
	Super::Interact(InOther);
	APawn* Pawn = Cast<APawn>(InOther);
	if (Pawn != nullptr)
	{
		UGameplayStatics::OpenLevel(this, TransferLevelName);
	}
}