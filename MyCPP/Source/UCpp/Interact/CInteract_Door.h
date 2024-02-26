// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interact/CInteract.h"
#include "CInteract_Door.generated.h"


UCLASS()
class UCPP_API ACInteract_Door : public ACInteract
{
	GENERATED_BODY()

	ACInteract_Door();
protected:
	/*UPROPERTY(EditDefaultsOnly)
		class USceneComponent* Scene;*/

	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* DoorFrame;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class UStaticMeshComponent* Door;

	UFUNCTION(BlueprintImplementableEvent)
		void Open();

	UFUNCTION(BlueprintImplementableEvent)
		void Close();

	virtual void Interact(AActor* InOther) override;

protected:
	virtual void BeginPlay() override;

	bool IsOpened;
};
