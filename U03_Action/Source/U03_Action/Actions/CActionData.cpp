// Fill out your copyright notice in the Description page of Project Settings.

#include "Actions/CActionData.h"
#include "Global.h"
#include "CEquipment.h"
#include "CAttachment.h"
#include "CDoAction.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"	


void UCActionData::BeginPlay(ACharacter* InOwnerCharacter)
{
	FTransform transform;
	//Attachment
	if(!!AttachmentClass)
	{
		Attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClass, transform, InOwnerCharacter);
		Attachment->SetActorLabel(InOwnerCharacter->GetActorLabel() + "_Attachment");
		UGameplayStatics::FinishSpawningActor(Attachment, transform);
	}
	//Equipment
	if (!!EquipmentClass)
	{
		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>
			(EquipmentClass, transform, InOwnerCharacter);
		Equipment->AttachToComponent(InOwnerCharacter->GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		Equipment->SetActorLabel(InOwnerCharacter->GetActorLabel() + "_Equipment");
		Equipment->SetData(EquipmentData);
		Equipment->SetColor(EquipmentColor);


		UGameplayStatics::FinishSpawningActor(Equipment, transform);
		if (!!Attachment)
		{
			Equipment->OnEquipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnEquip);
			Equipment->OnUnequipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnUnequip);
		}
		
	}

	if (!!DoActionClass)
	{
		DoAction = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACDoAction>(DoActionClass, transform, InOwnerCharacter);
		DoAction->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		DoAction->SetActorLabel(InOwnerCharacter->GetActorLabel() + "_DoAction");
		DoAction->SetDatas(DoActionDatas);
		UGameplayStatics::FinishSpawningActor(DoAction, transform);

		if (!!Attachment)
		{
			Attachment->OnAttamentBeginOverlap.AddDynamic(DoAction, &ACDoAction::OnAttachmentBeginOverlap);
			Attachment->OnAttamentEndOverlap.AddDynamic(DoAction, &ACDoAction::OnAttachmentEndOverlap);

			Attachment->OnAttachmentCollision.AddDynamic(DoAction, &ACDoAction::OnAttachmentCollision);
			Attachment->OffAttachmentCollision.AddDynamic(DoAction, &ACDoAction::OffAttachmentCollision);
		}
	}
}