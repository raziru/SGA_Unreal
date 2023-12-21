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
	Destroy();//강한 복사 약한 복사 문제

	
}

void ACItem::ShowData()
{
	CLog::Print(ItemData.ItemName.ToString());
	CLog::Print(ItemData.ItemDescription.ToString());
	CLog::Print(ItemData.CurrentStack);

}

void FItemData::ShowData()
{
	
	CLog::Log(ItemName.ToString());
	CLog::Log(CurrentStack);	
	CLog::Log(MaxStack);
	CLog::Log(ItemIndex);
	CLog::Log(ItemClass->GetName());
}

void FItemData::SetData(FItemData data)
{
	this->ItemType  = data.ItemType;
	this->ItemName  = data.ItemName;
	this->ItemClass = data.ItemClass;
	this->ItemDescription = data.ItemDescription;
	this->ItemImage = data.ItemImage;
	this->CurrentStack = data.CurrentStack;
	this->MaxStack  = data.MaxStack;
	this->ItemIndex = data.ItemIndex;

}
