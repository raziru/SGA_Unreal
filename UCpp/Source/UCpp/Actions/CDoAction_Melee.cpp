// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/CDoAction_Melee.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

void ACDoAction_Melee::DoAction()
{

	Super::DoAction();

	CheckFalse(Datas.Num() > 0);
	CheckFalse(State->IsIdleMode());
	State->SetActionMode();
	const FDoActionData& data = Datas[0];
	OwnerCharacter->PlayAnimMontage(data.AnimMontage, data.PlayRatio, data.StartSection);

	data.bCanMove ? Status->SetMove() : Status->SetStop();

}

void ACDoAction_Melee::Begin_DoAction()
{
	Super::Begin_DoAction();
}

void ACDoAction_Melee::End_DoAction()
{
	Super::End_DoAction();

	State->SetIdleMode();
	Status->SetMove();
}
