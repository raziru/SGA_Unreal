// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/CItem.h"
#include "CUserWidget_Inventory.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemSelected, FItemData, Item);

UCLASS()
class UCPP_API UCUserWidget_Inventory : public UUserWidget
{
	GENERATED_BODY()

public:
	//CUserWidget_Inventory(const TArray<class ACItem*>& Inventory, int MaxInventorySize, int ColumnSize);
	//void Construct();

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UUniformGridPanel* InventoryPanel;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> ItemButtonWidgetClass;
	

public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void BuildInventory(const TArray<FItemData>& Inventory, int MaxInventorySize, int ColumnSize);
	
	//UFUNCTION(BlueprintImplementableEvent)
	void ClearInventory();
	//UFUNCTION(BlueprintImplementableEvent)
	void RefreshInventory(const TArray<FItemData>& Inventory, int MaxInventorySize, int ColumnSize);


public:
	UFUNCTION(BlueprintCallable)
		void OnSelected(FItemData Item);

public:
	UPROPERTY(BlueprintAssignable)
		FItemSelected ItemSelected;
};
