// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interact/IInteract.h"
#include "CItem.generated.h"


UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon, Armor, Tool, Consumable, Max,
};

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		EItemType ItemType;

	UPROPERTY(EditAnywhere)
		FName ItemName;

	UPROPERTY(EditAnywhere)
		FText ItemDescription;

	UPROPERTY(EditAnywhere)
		class UTexture2D* ItemImage;

	UPROPERTY(EditAnywhere)
		int CurrentStack;

	UPROPERTY(EditAnywhere)
		int MaxStack;

	UPROPERTY(EditAnywhere)
		int ItemIndex;

};

UCLASS()
class UCPP_API ACItem : public AActor, public IIInteract
{
	GENERATED_BODY()
	
public:	
	ACItem();

	UFUNCTION(BlueprintPure)
		FORCEINLINE FItemData& GetItemData() { return ItemData; }

private:
	UPROPERTY(EditAnywhere)
		FItemData  ItemData;
public:

	virtual void Interact(AActor* InOther) override;

	void ShowData();

protected:
	virtual void BeginPlay() override;


	

};
