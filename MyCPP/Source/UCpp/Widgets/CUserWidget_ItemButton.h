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
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void SetItem(class ACItem* Item);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void MakeButtonStyle(class UTexture2D* Texture, int ItemCount, FName ItemName);

	UFUNCTION(BlueprintPure)
		FORCEINLINE class UTexture2D* GetTexture(class ACItem* Item) { return Item->GetItemData().ItemImage; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE int GetCount(class ACItem* Item)  { return Item->GetItemData().CurrentStack; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE FName GetName(class ACItem* Item) { return Item->GetItemData().ItemName; }
};
