
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IInteract.h"
#include "CInteract.generated.h"

UCLASS()
class UCPP_API ACInteract : public AActor, public IIInteract
{
	GENERATED_BODY()
	
public:	
	ACInteract();

	virtual void Interact(AActor* InOther) override;
protected:
	virtual void BeginPlay() override;

};
