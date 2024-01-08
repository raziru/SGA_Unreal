// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/CItem.h"
#include "Components/CActionComponent.h"
#include "CItem_Weapon.generated.h"



UCLASS()
class UCPP_API ACItem_Weapon : public ACItem
{
	GENERATED_BODY()

public: 
	FORCEINLINE UCActionData* GetData() { return ActionData; }
	FORCEINLINE EActionType   GetType() { return ActionType; }

protected:
	UPROPERTY(EditAnywhere)
		EActionType ActionType;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		UCActionData* ActionData;



	

};
