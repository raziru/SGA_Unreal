// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/CItem.h"
#include "Consumables/CConsumable.h"
#include "CItem_Consumable.generated.h"

UCLASS()
class UCPP_API ACItem_Consumable : public ACItem
{
	GENERATED_BODY()

public:
    FORCEINLINE TSubclassOf<ACConsumable> GetArmorClass() { return Consumable; }
private:

    UPROPERTY(EditAnywhere)
        TSubclassOf<ACConsumable> Consumable;

};
