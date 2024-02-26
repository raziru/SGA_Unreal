
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IInteract.h"
#include "CInteract.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndInteract);

UCLASS()
class UCPP_API ACInteract : public AActor, public IIInteract
{
	GENERATED_BODY()

public:	

	virtual void Interact(AActor* InOther) override;

	UPROPERTY(BlueprintAssignable)
		FEndInteract EndInteract;

protected:
	virtual void BeginPlay() override;

};
