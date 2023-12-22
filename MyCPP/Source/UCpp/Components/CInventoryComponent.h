// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory/CItem.h"
#include "Inventory/CItem_Weapon.h"
#include "Inventory/CItem_Armor.h"
#include "CInventoryComponent.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetNewItem, FItemData, NewItem);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSetNewAction, UCActionData*, NewItemAction, EActionType, NewItemActionType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetNewArmor, TSubclassOf<ACArmor>, armor);

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetNewItem, FItemData, NewItem);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetNewItem, FItemData, NewItem);

//������ ������ �ʿ��Ҽ� ������ multicast�� �����Ѵ�.

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
		TSubclassOf<UUserWidget> InventoryWidgetClass;

	UPROPERTY()
		class UCUserWidget_Inventory* InventoryWidget;
	

public:	
	// Sets default values for this component's properties
	UCInventoryComponent();

	void OpenInventory();

	void PickUp(ACItem* InItem);


private:
	UFUNCTION()
		void OnSelected(const FItemData NewItem);

protected:
	virtual void BeginPlay() override;

private:
	TArray<FItemData> Inventory;

	bool IsInventoryOpened;

public:
	UPROPERTY(BlueprintAssignable)
		FSetNewItem SetNewItem;

	UPROPERTY(BlueprintAssignable)
		FSetNewAction SetNewAction;

	UPROPERTY(BlueprintAssignable)
		FSetNewArmor SetNewArmor;
};
