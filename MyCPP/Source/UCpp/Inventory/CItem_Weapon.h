// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/CItem.h"
#include "Components/CActionComponent.h"
#include "CItem_Weapon.generated.h"


USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		EActionType ActionType;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		class UCActionData* ActionData;
};

UCLASS()
class UCPP_API ACItem_Weapon : public ACItem
{
	GENERATED_BODY()

public: 
	FORCEINLINE UCActionData* GetData() { return WeaponData.ActionData; }
	FORCEINLINE EActionType   GetType() { return WeaponData.ActionType; }

private:
	UPROPERTY(EditAnywhere)
		FWeaponData WeaponData;

};
