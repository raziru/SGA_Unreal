// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory/CItem.h"
#include "Inventory/CItem_Weapon.h"
#include "Inventory/CItem_Armor.h"
#include "Inventory/CItem_Consumable.h"
#include "CInventoryComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetNewItem, FItemData, NewItem);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSetNewMainWeapon, UCActionData*, NewItemAction, EActionType, NewItemActionType);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSetNewTool, UCActionData*, NewItemAction, bool, IsConsumable);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetNewArmor, TSubclassOf<ACArmor>, armor);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDropMainWeapon, UCActionData*, NewItemAction, EActionType, NewItemActionType);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDropTool, UCActionData*, NewItemAction, bool, IsConsumable);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDropArmor, TSubclassOf<ACArmor>, armor);

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetNewItem, FItemData, NewItem);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetNewItem, FItemData, NewItem);

//구현중 변경이 필요할수 있으니 multicast로 구현한다.

UCLASS( ClassGroup=(GameProject), meta=(BlueprintSpawnableComponent) )
class UCPP_API UCInventoryComponent : public UActorComponent
{
	GENERATED_BODY()


private:
	UPROPERTY(EditDefaultsOnly, Category = "InventorySize")
		int MaxInventorySize = 25;

	UPROPERTY(EditDefaultsOnly, Category = "InventorySize")
		int ColumnSize = 5;


protected:
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget>InventoryWidgetClass;
	UPROPERTY()
		class UCUserWidget_Inventory* InventoryWidget;
	

public:	
	// Sets default values for this component's properties
	UCInventoryComponent();
	void OpenInventory();
	void OpenInventory(EInventoryType NewInventoryType);

	void PickUp(ACItem* InItem);

	void EndToolAction();
	void DecreaseCount(FItemData NewItem);
private:
	UFUNCTION()
		void OnClicked(FItemData NewItem);
	UFUNCTION()
		void OnRightClicked(FItemData NewItem);

	UFUNCTION()
		void NextInventory();
	UFUNCTION()
		void PrevInventory();

protected:
	virtual void BeginPlay() override;

private:
	TArray<FItemData> Inventory;

	bool IsInventoryOpened;

	bool IsConsumable;
	
	FItemData ChangedItem;

	EItemType SelectedItemType;

	EInventoryType InventoryType;
public:
	UPROPERTY(BlueprintAssignable)
		FSetNewItem SetNewItem;

	UPROPERTY(BlueprintAssignable)
		FSetNewMainWeapon SetNewMainWeapon;

	UPROPERTY(BlueprintAssignable)
		FSetNewArmor SetNewArmor;

	UPROPERTY(BlueprintAssignable)
		FSetNewTool SetNewTool;

	UPROPERTY(BlueprintAssignable)
		FDropMainWeapon DropMainWeapon;

	UPROPERTY(BlueprintAssignable)
		FDropArmor DropArmor;

	UPROPERTY(BlueprintAssignable)
		FDropTool DropTool;
};
