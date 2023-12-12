// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CInventoryComponent.h"
#include "Interact/IInteract.h"
#include "CItem.generated.h"


UCLASS()
class UCPP_API ACItem : public AActor, public IIInteract
{
	GENERATED_BODY()
	
public:	
	ACItem();

private:
	UPROPERTY(EditAnywhere)
		FItemData  ItemData;
public:

	virtual void Interact() override;

protected:
	virtual void BeginPlay() override;


	

};
