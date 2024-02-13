#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPickupComponent.generated.h"


UCLASS( ClassGroup=(GameProject), meta=(BlueprintSpawnableComponent) )
class UCPP_API UCPickupComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCPickupComponent();

	void Pickup(AActor* InOther);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		TArray<class ACItem*> Items;
	
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		TMap<TSubclassOf<class ACItem>,int> ItemClasses;

};
