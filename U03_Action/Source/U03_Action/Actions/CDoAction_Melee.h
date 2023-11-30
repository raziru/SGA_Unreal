// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Melee.generated.h"


UCLASS()
class U03_ACTION_API ACDoAction_Melee : public ACDoAction
{
	GENERATED_BODY()

public:
	FORCEINLINE void EnableCombo() { bEnable = true; }
	FORCEINLINE void DisableCombo() { bEnable = false; }
public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;//combo 전환 delay 감소
	virtual void End_DoAction() override;

private:
	bool bExist;
	bool bEnable;
	bool bLast;

	int32 Index;

};
