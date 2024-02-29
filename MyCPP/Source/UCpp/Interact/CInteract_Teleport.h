
#pragma once

#include "CoreMinimal.h"
#include "Interact/CInteract.h"
#include "CInteract_Teleport.generated.h"


UCLASS()
class UCPP_API ACInteract_Teleport : public ACInteract
{
	GENERATED_BODY()


public:

	virtual void Interact(AActor* InOther) override;

protected:
	//virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		FName TransferLevelName;

};
