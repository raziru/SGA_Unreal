// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/CItem.h" 
#include "Components/CStatusComponent.h"
#include "Components/CEquipComponent.h"
#include "CItem_Armor.generated.h"



UCLASS()
class UCPP_API ACItem_Armor : public ACItem
{
	GENERATED_BODY()
public:
    FORCEINLINE FStatusData GetStatus() { return StatusData; }

private:
    UPROPERTY(EditAnywhere)
        FStatusData StatusData;

    UPROPERTY(EditAnywhere)
        EArmorType EArmorType;

    
	
};
