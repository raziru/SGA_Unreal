

#include "CAction.h"
#include "Actions/CEquipment.h"
#include "Actions/CAttachment.h"
#include "Actions/CDoAction.h"



void UCAction::DataDestroy()
{
	Equipment->Destroy();
	Attachment->Destroy();
	DoAction->Destroy();
}
