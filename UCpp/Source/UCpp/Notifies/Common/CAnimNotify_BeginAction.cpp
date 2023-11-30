// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/Common/CAnimNotify_BeginAction.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Actions/CActionData.h"
#include "Actions/CDoAction.h"
#include "Components/CActionComponent.h"

FString UCAnimNotify_BeginAction::GetNotifyName_Implementation() const
{
	return "BeginAction";
}

void UCAnimNotify_BeginAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* action = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(action);

	action->GetCurrent()->GetDoAction()->Begin_DoAction();
}
