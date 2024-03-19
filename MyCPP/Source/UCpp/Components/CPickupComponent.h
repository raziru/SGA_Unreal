#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "CPickupComponent.generated.h"

USTRUCT(BlueprintType)
struct FItemTableData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACItem> item;

	UPROPERTY(EditAnywhere)
		int Count = 1;


};

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

	UPROPERTY(EditAnywhere, Category = "DataTable")
		UDataTable* DataTable;


private:
	UPROPERTY(EditAnywhere)
		bool IsRand;
	UPROPERTY(EditAnywhere)
		bool IsOpened;
};
