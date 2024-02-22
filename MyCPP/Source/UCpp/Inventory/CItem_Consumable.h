// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CItem.h"
#include "Components/CActionComponent.h"
#include "Components/CStatusComponent.h"
#include "CItem_Weapon.h"
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
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Potion")
		FStatusData ItemStatus;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Potion")
		float Health;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Potion")
		float Mana;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Magic")
		TSubclassOf<ACItem_Weapon> Weapon;

protected:
	UPROPERTY(EditAnywhere)
		EActionType ActionType;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		UCActionData* ActionData;
	

};
