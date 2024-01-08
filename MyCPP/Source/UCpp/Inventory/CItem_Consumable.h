// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/CItem.h"
#include "Components/CActionComponent.h"
#include "CItem_Consumable.generated.h"

UCLASS()
class UCPP_API ACItem_Consumable : public ACItem
{
	GENERATED_BODY()

//public:
//    FORCEINLINE TSubclassOf<ACConsumable> GetArmorClass() { return Consumable; }
//private:
//
//    UPROPERTY(EditAnywhere)
//        TSubclassOf<ACConsumable> Consumable;
public:
	FORCEINLINE UCActionData* GetData() { return ActionData; }
	FORCEINLINE EActionType   GetType() { return ActionType; }

protected:
	UPROPERTY(EditAnywhere)
		EActionType ActionType;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		UCActionData* ActionData;
};
