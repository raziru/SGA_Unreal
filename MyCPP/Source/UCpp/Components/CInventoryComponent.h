// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory/CItem.h"
#include "CInventoryComponent.generated.h"

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

protected:
	virtual void BeginPlay() override;

private:
	TArray<ACItem*> Inventory;

	bool IsInventoryOpened;

};
