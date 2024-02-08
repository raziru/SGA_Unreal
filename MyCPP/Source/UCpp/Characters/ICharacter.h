// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICharacter.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UICharacter : public UInterface
{
	GENERATED_BODY()
};

class UCPP_API IICharacter
{
	GENERATED_BODY()

public:
	virtual void ChangeColor(FLinearColor InColor) = 0;
	virtual void Interact() {}
	virtual void Begin_Dead() {}
	virtual void End_Dead() {}
	virtual void End_Backstep() {}

	virtual void OnDefaultMode() {}

	virtual void PickUp(class ACItem* InItem) {}

};
