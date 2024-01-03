// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_ActionButton.generated.h"

/**
 * 
 */
UCLASS()
class UCPP_API UCUserWidget_ActionButton : public UUserWidget
{
	GENERATED_BODY()
protected:
    UFUNCTION(BlueprintCallable)
        void Click();

    UFUNCTION(BlueprintCallable)
        void Hover();

    UFUNCTION(BlueprintCallable)
        void Unhover();

private:
    //class UCUserWidget_ActionList* GetActionList();
};
