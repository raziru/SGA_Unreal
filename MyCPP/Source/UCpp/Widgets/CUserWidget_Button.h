// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Button.generated.h"


UCLASS()
class UCPP_API UCUserWidget_Button : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		class ACItem* item;
};
