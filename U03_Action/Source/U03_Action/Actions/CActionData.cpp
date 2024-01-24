// Fill out your copyright notice in the Description page of Project Settings.

#include "Actions/CActionData.h"
#include "Global.h"
#include "CAction.h"
#include "CEquipment.h"
#include "CAttachment.h"
#include "CDoAction.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"	


void UCActionData::BeginPlay(ACharacter* InOwnerCharacter, class UCAction** OutAction)
{
	FTransform transform;
	//Attachment
	ACAttachment* attachment = NULL;
	if(!!AttachmentClass)
	{
		attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClass, transform, InOwnerCharacter);
		attachment->SetActorLabel(GetLableName(InOwnerCharacter, "_Attachment"));
		UGameplayStatics::FinishSpawningActor(attachment, transform);
	}
	//Equipment
	ACEquipment* equipment = NULL;
	if (!!EquipmentClass)
	{
		equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>
			(EquipmentClass, transform, InOwnerCharacter);
		equipment->AttachToComponent(InOwnerCharacter->GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		equipment->SetActorLabel(GetLableName(InOwnerCharacter,"_Equipment"));
		equipment->SetData(EquipmentData);
		equipment->SetColor(EquipmentColor);

		
		UGameplayStatics::FinishSpawningActor(equipment, transform);
		if (!!attachment)
		{
			equipment->OnEquipmentDelegate. AddDynamic(attachment, &ACAttachment::OnEquip);
			equipment->OnUnequipmentDelegate.AddDynamic(attachment, &ACAttachment::OnUnequip);
		}
		
	}

	ACDoAction* doAction = NULL;
	if (!!DoActionClass)
	{
		doAction = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACDoAction>(DoActionClass, transform, InOwnerCharacter);
		doAction->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		doAction->SetActorLabel(GetLableName(InOwnerCharacter, "_DoAction"));
		doAction->SetDatas(DoActionDatas);
		UGameplayStatics::FinishSpawningActor(doAction, transform);

		if (!!equipment)
		{
			doAction->SetEquipped(equipment->GetEquipped());
		}

		if (!!attachment)
		{
			attachment->OnAttamentBeginOverlap.AddDynamic(doAction, &ACDoAction::OnAttachmentBeginOverlap);
			attachment->OnAttamentEndOverlap.AddDynamic(doAction, &ACDoAction::OnAttachmentEndOverlap);

			attachment->OnAttachmentCollision.AddDynamic(doAction, &ACDoAction::OnAttachmentCollision);
			attachment->OffAttachmentCollision.AddDynamic(doAction, &ACDoAction::OffAttachmentCollision);
		}
	}

	*OutAction = NewObject<UCAction>();
	(*OutAction)->Attachment = attachment;
	(*OutAction)->Equipment = equipment;
	(*OutAction)->DoAction = doAction;
	(*OutAction)->EquipmentColor = EquipmentColor;

}
//옮길때 고치자
FString UCActionData::GetLableName(class ACharacter* InOwnerCharacter, FString InName)
{
	FString str;
	str.Append(InOwnerCharacter->GetActorLabel());
	str.Append("_");
	str.Append(InName);
	str.Append("_");
	str.Append(GetName().Replace(L"DA_", L""));

	return str;
}