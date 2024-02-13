
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IInteract.h"
#include "CChest.generated.h"

UCLASS()
class UCPP_API ACChest : public AActor
{
	GENERATED_BODY()
	
public:	
	ACChest();

	//virtual void Interact(AActor* InOther) override;

protected:
	virtual void BeginPlay() override;

private:

};
