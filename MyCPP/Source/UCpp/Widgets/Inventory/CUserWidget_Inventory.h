// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/CItem.h"
#include "CUserWidget_Inventory.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemClicked,FItemData, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemRightClicked, FItemData, Item);


UCLASS()
class UCPP_API UCUserWidget_Inventory : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UUniformGridPanel* InventoryPanel;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> ItemButtonWidgetClass;
	

public:

	UFUNCTION(BlueprintCallable)
		void BuildInventory(const TArray<FItemData>& Inventory, int MaxInventorySize, int ColumnSize);
	
	void ClearInventory();

	void RefreshInventory(const TArray<FItemData>& Inventory, int MaxInventorySize, int ColumnSize);


public:
	UFUNCTION(BlueprintCallable)
		void OnClicked(FItemData Item);

	UFUNCTION(BlueprintCallable)
		void OnRightClicked(FItemData Item);

public:
	UPROPERTY(BlueprintAssignable)
		FItemClicked ItemClicked;

	UPROPERTY(BlueprintAssignable)
		FItemRightClicked ItemRightClicked;
};
