// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory/CItem.h"
#include "CInventoryComponent.generated.h"

UCLASS( ClassGroup=(GameProject), meta=(BlueprintSpawnableComponent) )
class UCPP_API UCInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCInventoryComponent();

	void OpenInventory();

	void PickUp(ACItem* InItem);

protected:
	virtual void BeginPlay() override;

private:
	TArray<ACItem*> Inventory;

};
