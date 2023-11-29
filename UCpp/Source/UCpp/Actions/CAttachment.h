// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAttachment.generated.h"

UCLASS()
class UCPP_API ACAttachment : public AActor
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)//Can use in blueprint
		void AttachTo(FName InSocketName);
public:	
	ACAttachment();

protected:
	virtual void BeginPlay() override;
public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnEquip();

	UFUNCTION(BlueprintImplementableEvent)
		void OnUnequip();

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;

	UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* Status;

};
