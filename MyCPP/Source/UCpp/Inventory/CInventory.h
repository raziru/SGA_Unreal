// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CItem.h"
#include "Components/CInventoryComponent.h"
#include "CInventory.generated.h"



UCLASS()
class UCPP_API ACInventory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACInventory();

	UFUNCTION(BlueprintCallable)
		void PickUp(FItemData ItemData);

	UFUNCTION(BlueprintCallable)
		void OpenInventory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;




};
