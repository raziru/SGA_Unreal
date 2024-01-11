// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Health.generated.h"


UCLASS()
class UCPP_API UCUserWidget_Health : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
		void Update(float Health, float MaxHealth);
	
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateMana(float Mana, float MaxMana);
};
