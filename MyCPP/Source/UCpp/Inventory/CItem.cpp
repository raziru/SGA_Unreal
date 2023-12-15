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

void ACItem::Interact(AActor* InOther)
{
	ACPlayer* Player = Cast<ACPlayer>(InOther);
	CheckNull(Player);
	Player->PickUp(this);
	CLog::Print(InOther->GetName());
	//Destroy();//강한 복사 약한 복사 문제

	
}

void ACItem::ShowData()
{
	CLog::Print(ItemData.ItemName.ToString());
	CLog::Print(ItemData.ItemDescription.ToString());
	CLog::Print(ItemData.CurrentStack);

}


