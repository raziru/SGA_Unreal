#include "Inventory/CItem.h"
#include "Global.h"
#include "Characters/CPlayer.h"

ACItem::ACItem()
{

}

void ACItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACItem::Interact()
{
//	character
	Destroy();
}


