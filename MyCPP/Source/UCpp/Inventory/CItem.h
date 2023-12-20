// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Components/CActionComponent.h"
#include "Interact/IInteract.h"
#include "CItem.generated.h"


UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon, Armor, Tool, Consumable, Max,
};

//USTRUCT(BlueprintType)
//struct WeaponData : public FTableRowBase
//{
//	GENERATED_BODY()
//
//		UPROPERTY(EditAnywhere)
//		FName ItemName;
//
//	UPROPERTY(EditAnywhere)
//		EActionType ActionType;
//
//	UPROPERTY(EditAnywhere, BluePrintReadWrite)
//		class UCActionData* ActionData;
//};
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

	UPROPERTY(EditAnywhere)
		EActionType ActionType;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		class UCActionData* ActionData;
	

public:
	void ShowData();
	void SetData(FItemData data);
	
};


//USTRUCT(BlueprintType)
//struct FItemClass:public FTableRowBase
//{
//	GENERATED_BODY()
//
//public:
//	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Item")
//		FName ItemName;
//	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Item")
//		EActionType ActionType;
//	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Item")
//		class UCActionData* Actiondata;
//
//};

UCLASS()
class UCPP_API ACItem : public AActor, public IIInteract
{
	GENERATED_BODY()
	
public:	
	ACItem();

	//ACItem(const ACItem& Item);

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
