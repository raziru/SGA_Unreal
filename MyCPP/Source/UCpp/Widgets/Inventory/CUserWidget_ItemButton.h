// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/CItem.h"
#include "CUserWidget_ItemButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FClicked, FItemData, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRightClicked, FItemData, Item);

UCLASS()
class UCPP_API UCUserWidget_ItemButton : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* ItemButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* ItemName;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* ItemQuantity; 
	

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void MakeItemButton(const FItemData Item);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void MakeEmptyButton();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void SetItem(const FItemData Item);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void MakeButtonStyle(class UTexture2D* Texture, int ItemCount, FName Name);

	UFUNCTION(BlueprintPure)
		FORCEINLINE class UTexture2D* GetTexture(const FItemData Item) { return Item.ItemImage; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE int GetCount(const FItemData Item)  { return Item.CurrentStack; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE FName GetName(const FItemData Item) { return Item.ItemName; }

	UFUNCTION(BlueprintCallable)
		void ButtonClicked(const FItemData Item);

	UFUNCTION(BlueprintCallable)
		void ButtonRightClicked(const FItemData Item);
public:
	UPROPERTY(BlueprintAssignable)
		FClicked Clicked;

	UPROPERTY(BlueprintAssignable)
		FRightClicked RightClicked;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FItemData Data;
};
