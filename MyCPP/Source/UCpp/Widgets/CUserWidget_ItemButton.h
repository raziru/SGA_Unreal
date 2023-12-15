// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_ItemButton.generated.h"


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
		void SetItem(const class ACItem* Item);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void MakeButtonStyle(class UTexture2D* Texture, int ItemCount, FName Name);

	UFUNCTION(BlueprintPure)
		FORCEINLINE class UTexture2D* GetTexture(class ACItem* Item) { return Item->GetItemData().ItemImage; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE int GetCount(class ACItem* Item)  { return Item->GetItemData().CurrentStack; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE FName GetName(class ACItem* Item) { return Item->GetItemData().ItemName; }
};
