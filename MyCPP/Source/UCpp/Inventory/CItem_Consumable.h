// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/CItem.h"
#include "Components/CActionComponent.h"
#include "Components/CStatusComponent.h"
#include "CItem_Consumable.generated.h"

UCLASS()
class UCPP_API ACItem_Consumable : public ACItem
{
	GENERATED_BODY()

public:
	FORCEINLINE UCActionData* GetData() { return ActionData; }
	FORCEINLINE EActionType   GetType() { return ActionType; }
	
	UFUNCTION(BlueprintImplementableEvent)
		void ConsumableEvent();

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FStatusData ItemStatus;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Health;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Mana;

protected:
	UPROPERTY(EditAnywhere)
		EActionType ActionType;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		UCActionData* ActionData;
	

};
