

#include "CAction.h"
#include "Actions/CEquipment.h"
#include "Actions/CDoAction.h"



void UCAction::OnSecondAttachment(ACAttachment* NewSecondAttachment)
{
	if (!!NewSecondAttachment)
	{
		Attachments[(int32)EAttachment::SecondHand] = NewSecondAttachment;
		Equipment->OnEquipmentDelegate.AddDynamic(NewSecondAttachment, &ACAttachment::OnEquip);
		Equipment->OnUnequipmentDelegate.AddDynamic(NewSecondAttachment, &ACAttachment::OnUnequip);

	}
}

void UCAction::OffSecondAttachment(ACAttachment* NewSecondAttachment)
{
	if (!!NewSecondAttachment)
	{
		Attachments[(int32)EAttachment::SecondHand] = NULL;

	}
}

void UCAction::AttachmentOnCollision()
{
	for (ACAttachment* attachment : Attachments)
	{
		if (!!attachment)
		{
			attachment->OnCollision();
		}
	}
}

void UCAction::AttachmentOffCollision()
{
	for (ACAttachment* attachment : Attachments)
	{
		if (!!attachment)
		{
			attachment->OffCollision();
		}
	}
}

bool UCAction::GetAttachment()
{
	for (ACAttachment* attachment : Attachments)
	{
		if (!!attachment)
		{
			return true;
		}
	}
	return false;
}

void UCAction::DestroyActor()
{
	for (ACAttachment* attachment : Attachments)
	{
		if (!!attachment)
		{
			attachment->Destroy();
		}
	}
	Equipment->Destroy();
	DoAction->DestroyAll();
}
