
#include "CDoAction_Tool.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Actions/CAttachment.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"	

void ACDoAction_Tool::BeginPlay()
{
	Super::BeginPlay();
	FTransform transform;

	if (!!AttachmentClass)
	{
		Attachment = OwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClass, transform, OwnerCharacter);
		Attachment->SetActorLabel(GetLabelName(OwnerCharacter, "_ToolAttachment"));
		UGameplayStatics::FinishSpawningActor(Attachment, transform);
	}
}

void ACDoAction_Tool::DoAction()
{
	CheckFalse(State->IsIdleMode());
	State->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRatio, Datas[0].StartSection);
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Tool::Begin_DoAction()
{
	Attachment->OnEquip();
}

void ACDoAction_Tool::End_DoAction()
{
	if (EndAction.IsBound())
	{
		EndAction.Broadcast();
	}
	Attachment->OnUnequip();
	State->SetIdleMode();
	Status->SetMove();
}


FString ACDoAction_Tool::GetLabelName(class ACharacter* InOwnerCharacter, FString InName)
{
	FString str;
	str.Append(InOwnerCharacter->GetActorLabel());
	str.Append("_");
	str.Append(InName);
	str.Append("_");
	str.Append(GetName().Replace(L"DA_", L""));

	return str;
}
