// Fill out your copyright notice in the Description page of Project Settings.

#include "Actions/CActionData.h"
#include "Global.h"
#include "CEquipment.h"
#include "CAttachment.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"	


void UCActionData::BeginPlay(ACharacter* InOwnerCharacter)
{
	FTransform transform;
	//Attachment
	{
		Attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClass, transform, InOwnerCharacter);
		Attachment->SetActorLabel(InOwnerCharacter->GetActorLabel() + "_Attachment");
		UGameplayStatics::FinishSpawningActor(Attachment, transform);
	}
	//Equipment
	{
		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>
			(EquipmentClass, transform, InOwnerCharacter);
		Equipment->AttachToComponent(InOwnerCharacter->GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		Equipment->SetActorLabel(InOwnerCharacter->GetActorLabel() + "_Equipment");
		Equipment->SetData(EquipmentData);

		UGameplayStatics::FinishSpawningActor(Equipment, transform);

		Equipment->OnEquipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnEquip);
		Equipment->OnUnequipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnUnequip);
	}
}