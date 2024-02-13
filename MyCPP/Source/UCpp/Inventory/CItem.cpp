#include "Inventory/CItem.h"
#include "Global.h"
#include "Components/CInventoryComponent.h"

ACItem::ACItem()
{

}

void ACItem::BeginPlay()
{
	Super::BeginPlay();
}

void ACItem::Interact(AActor* InOther)
{
	/*ACPlayer* Player = Cast<ACPlayer>(InOther);
	CheckNull(Player);
	Player->PickUp(this);*/

	UCInventoryComponent* Inventory = CHelpers::GetComponent<UCInventoryComponent>(InOther);
	CheckNull(Inventory);
	
	Inventory->Pickup(this);
	
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

void FItemData::operator=(const FItemData& other)
{
	this->ItemType =        other.ItemType;
	this->ItemName =        other.ItemName;
	this->ItemClass =       other.ItemClass;
	this->ItemDescription = other.ItemDescription;
	this->ItemImage =       other.ItemImage;
	this->CurrentStack =    other.CurrentStack;
	this->MaxStack =        other.MaxStack;
	this->ItemIndex =       other.ItemIndex;
}
bool FItemData::operator==(const FItemData& other)
{
	if ((this->ItemType == other.ItemType) &&
		(this->ItemName == other.ItemName) &&
		(this->ItemClass == other.ItemClass) &&
		(this->ItemIndex == other.ItemIndex)) {
		return true;
	}


	return false;

}