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
	//CUserWidget_Inventory(const TArray<class ACItem*>& Inventory, int MaxInventorySize, int ColumnSize);
	//void Construct();

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UUniformGridPanel* InventoryPanel;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> ItemButtonWidgetClass;
	

public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void BuildInventory(const TArray<class ACItem*>& Inventory, int MaxInventorySize, int ColumnSize);
	
	//UFUNCTION(BlueprintImplementableEvent)
	void ClearInventory();
	//UFUNCTION(BlueprintImplementableEvent)
	void RefreshInventory(const TArray<class ACItem*>& Inventory, int MaxInventorySize, int ColumnSize);


};
