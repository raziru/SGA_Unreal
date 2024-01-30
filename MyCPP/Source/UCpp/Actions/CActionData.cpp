// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/CActionData.h"
#include "Global.h"
#include "CEquipment.h"
#include "CDoAction.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"	

void UCActionData::BeginPlay(ACharacter* InOwnerCharacter, UCAction** OutAction)
{
	FTransform transform;

	
	//ACAttachment* attachment = NULL;
	////Attachment
	//if(!!AttachmentClass)
	//{
	//	attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClass, transform, InOwnerCharacter);
	//	attachment->SetActorLabel(GetLabelName(InOwnerCharacter,"_Attachment"));
	//	UGameplayStatics::FinishSpawningActor(attachment, transform);
	//}



	//ACAttachment* secondAttachment = NULL;
	////Attachment
	//if (!!SecondAttachmentClass)
	//{
	//	secondAttachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(SecondAttachmentClass, transform, InOwnerCharacter);
	//	secondAttachment->SetActorLabel(GetLabelName(InOwnerCharacter, "_Attachment"));
	//	UGameplayStatics::FinishSpawningActor(secondAttachment, transform);
	//}

	ACAttachment* attachments[(int32)EAttachment::Max] = {};

	//Attachment
	if (!!AttachmentClasses[(int32)EAttachment::MainHand])
	{
		attachments[(int32)EAttachment::MainHand] = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClasses[(int32)EAttachment::MainHand], transform, InOwnerCharacter);
		attachments[(int32)EAttachment::MainHand]->SetActorLabel(GetLabelName(InOwnerCharacter, "_Attachment_MainHand"));
		UGameplayStatics::FinishSpawningActor(attachments[(int32)EAttachment::MainHand], transform);
	}

	if (!!AttachmentClasses[(int32)EAttachment::SecondHand])
	{
		attachments[(int32)EAttachment::SecondHand] = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClasses[(int32)EAttachment::SecondHand], transform, InOwnerCharacter);
		attachments[(int32)EAttachment::SecondHand]->SetActorLabel(GetLabelName(InOwnerCharacter, "_Attachment_SecondHand"));
		UGameplayStatics::FinishSpawningActor(attachments[(int32)EAttachment::SecondHand], transform);
	}

	if (!!AttachmentClasses[(int32)EAttachment::Projectile])
	{
		attachments[(int32)EAttachment::Projectile] = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClasses[(int32)EAttachment::Projectile], transform, InOwnerCharacter);
		attachments[(int32)EAttachment::Projectile]->SetActorLabel(GetLabelName(InOwnerCharacter, "_Attachment_Projectile"));
		UGameplayStatics::FinishSpawningActor(attachments[(int32)EAttachment::Projectile], transform);
	}



	//Equipment
	ACEquipment* equipment = NULL;
	if(!!EquipmentClass)
	{
		equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>
			(EquipmentClass, transform, InOwnerCharacter);
		equipment->AttachToComponent(InOwnerCharacter->GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		equipment->SetActorLabel(GetLabelName(InOwnerCharacter,"_Equipment"));
		equipment->SetData(EquipmentData);
		equipment->SetColor(EquipmentColor);

		UGameplayStatics::FinishSpawningActor(equipment, transform);

		for (int32 i = 0; i < (int32)EAttachment::Max; i++)
		{
			if (!!attachments[i])
			{
				if (!!equipment)
				{
					equipment->OnEquipmentDelegate.AddDynamic(attachments[i], &ACAttachment::OnEquip);
					equipment->OnUnequipmentDelegate.AddDynamic(attachments[i], &ACAttachment::OnUnequip);
				}	
			}			
		}
	}
	ACDoAction* doAction = NULL;
	if (!!DoActionClass)
	{
		doAction = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACDoAction>(DoActionClass, transform, InOwnerCharacter);
		doAction->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		doAction->SetActorLabel(GetLabelName(InOwnerCharacter,"_DoAction"));
		doAction->SetDatas(DoActionDatas);
		UGameplayStatics::FinishSpawningActor(doAction, transform);

		if (!!equipment)
		{
			doAction->SetEquipped(equipment->GetEquipped());
		}

		for (int32 i = 0; i < (int32)EAttachment::Max; i++)
		{
			if (!!attachments[i])
			{
				if (!!doAction)
				{
					attachments[i]->OnAttachmentBeginOverlap.AddDynamic(doAction, &ACDoAction::OnAttachmentBeginOverlap);
					attachments[i]->OnAttachmentEndOverlap.AddDynamic(doAction, &ACDoAction::OnAttachmentEndOverlap);
					attachments[i]->OnAttachmentCollision.AddDynamic(doAction, &ACDoAction::OnAttachmentCollision);
					attachments[i]->OffAttachmentCollision.AddDynamic(doAction, &ACDoAction::OffAttachmentCollision);
				}
				
			}
			
		}
	}
	*OutAction = NewObject<UCAction>();
	//(*OutAction)->Attachment = attachment;
	//(*OutAction)->SecondAttachment = secondAttachment;
	
	for (int32 i = 0; i < (int32) EAttachment::Max; i++)
	{
		(*OutAction)->Attachments[i] = attachments[i];
	}

	(*OutAction)->Equipment = equipment;
	(*OutAction)->DoAction = doAction;
	(*OutAction)->EquipmentColor = EquipmentColor;
}


FString UCActionData::GetLabelName(class ACharacter* InOwnerCharacter, FString InName)
{
	FString str;
	str.Append(InOwnerCharacter->GetActorLabel());
	str.Append("_");
	str.Append(InName);
	str.Append("_");
	str.Append(GetName().Replace(L"DA_", L""));

	return str;
}

void UCActionData::DataDestroy()
{
	/*Equipment->Destroy();
	Attachment->Destroy();
	DoAction->Destroy();*/
}
