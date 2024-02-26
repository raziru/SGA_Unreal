#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/CItem.h"
#include "CUserWidget_Inventory.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemClicked,FItemData, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemRightClicked, FItemData, Item);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPrevInventory);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNextInventory);

UCLASS()
class UCPP_API UCUserWidget_Inventory : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UUniformGridPanel* InventoryPanel;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> ItemButtonWidgetClass;

	void SetInventoryType(EInventoryType NewInventoryType);

private:
	EInventoryType InventoryType;

public:

	UFUNCTION(BlueprintCallable)
		void BuildInventory(const TArray<FItemData>& Inventory, int MaxInventorySize, int ColumnSize);
	
	void RefreshInventory(const TArray<FItemData>& Inventory, int MaxInventorySize, int ColumnSize);

	UFUNCTION(BlueprintCallable)
		void OnPrevInventory();

	UFUNCTION(BlueprintCallable)
		void OnNextInventory();
	
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateInventoryName(FName Name);

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

	UPROPERTY(BlueprintAssignable)
		FPrevInventory PrevInventory;

	UPROPERTY(BlueprintAssignable)
		FNextInventory NextInventory;
};
