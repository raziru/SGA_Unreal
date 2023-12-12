// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CInventoryComponent.generated.h"


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

UCLASS( ClassGroup=(GamePlay), meta=(BlueprintSpawnableComponent) )
class UCPP_API UCInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCInventoryComponent();

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;




		
};
