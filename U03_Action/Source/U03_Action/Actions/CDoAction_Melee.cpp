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

	if (bEnable == true)
	{
		bExist = true;
		bEnable = false;

		return;
	}

	CheckFalse(State->IsIdleMode());
	State->SetActionMode();
	const FDoActionData& data = Datas[0];
	OwnerCharacter->PlayAnimMontage(data.AnimMontage, data.PlayRatio, data.StartSection);

	data.bCanMove ? Status->SetMove() : Status->SetStop();

}

void ACDoAction_Melee::Begin_DoAction()
{
	Super::Begin_DoAction();

	CheckFalse(bExist);
	bExist = false;


	OwnerCharacter->StopAnimMontage();

	Index++;

	const FDoActionData& data = Datas[Index];
	OwnerCharacter->PlayAnimMontage(data.AnimMontage, data.PlayRatio, data.StartSection);

	data.bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Melee::End_DoAction()
{
	Super::End_DoAction();

	const FDoActionData& data = Datas[Index];
	OwnerCharacter->StopAnimMontage(data.AnimMontage);

	State->SetIdleMode();
	Status->SetMove();

	Index = 0;
}
void ACDoAction_Melee::OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter)
{
	//CLog::Log(InOtherCharacter->GetName());

	FDamageEvent e;//이벤트를 요구해서 빈공간 넣어주는 것이다.
	InOtherCharacter->TakeDamage(Datas[Index].Power, e, OwnerCharacter->GetController(), this);
}
void ACDoAction_Melee::OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter)
{

}

void ACDoAction_Melee::OnAttachmentCollision()
{

}
void ACDoAction_Melee::OffAttachmentCollision() 
{

}