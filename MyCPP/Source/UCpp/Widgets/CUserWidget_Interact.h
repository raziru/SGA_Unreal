// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Interact.generated.h"


UCLASS()
class UCPP_API UCUserWidget_Interact : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
		void Update(const FString& Name, const FString& Text);
	/*UFUNCTION(BlueprintCallable)
		FString LastWord(const FString& Word);*/
};
