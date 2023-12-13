// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteract.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIInteract : public UInterface
{
	GENERATED_BODY()
};

class UCPP_API IIInteract
{
	GENERATED_BODY()

public:
	//virtual void Interact() {}
	virtual void Interact(AActor* InOther) {}
};
