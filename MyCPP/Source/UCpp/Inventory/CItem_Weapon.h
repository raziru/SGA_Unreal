// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/CItem.h"
#include "CItem_Weapon.generated.h"


USTRUCT(BlueprintType)
struct FItemData_Weapon :public FItemData
{
	GENERATED_BODY()

//public:
//	UPROPERTY(EditAnywhere)
//		EActionType ActionType;
//	UPROPERTY(EditAnywhere, BluePrintReadWrite)
//		class UCActionData* ActionData;
};

UCLASS()
class UCPP_API ACItem_Weapon : public ACItem
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
		FItemData_Weapon WeaponData;

};
