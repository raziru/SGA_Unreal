// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Inventory.generated.h"

UCLASS()
class UCPP_API UCUserWidget_Inventory : public UUserWidget
{
	GENERATED_BODY()
	



public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void RefreshInventory(const TArray<class ACItem*>& Inventory, int MaxInventorySize, int ColumnSize);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void ClearInventory();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void BuildInventory(const TArray<class ACItem*>& Inventory, int MaxInventorySize, int ColumnSize);

};
