// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/CItem.h" 
#include "Armors/CArmor.h"
#include "CItem_Armor.generated.h"



UCLASS()
class UCPP_API ACItem_Armor : public ACItem
{
	GENERATED_BODY()

public:
    FORCEINLINE TSubclassOf<ACArmor> GetArmorClass() { return Armor; }
private:

    UPROPERTY(EditAnywhere)
        TSubclassOf<ACArmor> Armor;

    
	
};
