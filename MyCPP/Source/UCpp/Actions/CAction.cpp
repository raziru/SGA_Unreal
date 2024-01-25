

#include "CAction.h"
#include "Actions/CEquipment.h"
#include "Actions/CAttachment.h"
#include "Actions/CDoAction.h"



void UCAction::DestroyActor()
{
	Equipment->Destroy();
	Attachment->Destroy();
	DoAction->DestroyAll();
}
