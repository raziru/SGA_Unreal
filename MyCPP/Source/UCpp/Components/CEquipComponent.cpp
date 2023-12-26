// Fill out your copyright notice in the Description page of Project Settings.


#include "CEquipComponent.h"
#include "Global.h"
#include "Armors/CArmor.h"
#include "GameFramework/Character.h"


UCEquipComponent::UCEquipComponent()
{

}




void UCEquipComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void UCEquipComponent::SetNewArmor(TSubclassOf<class ACArmor> NewArmorClass)
{
	ACArmor* NewArmor;

	NewArmor = Cast<ACArmor>(GetWorld()->SpawnActor(NewArmorClass));

	CheckNull(NewArmor);

	for (TPair<EArmorType, ACArmor*> Armor : Armors)
	{
		if (Armor.Value->GetClass() == NewArmorClass)
		{
			Armor.Value->UnEquip();
			Armors.Remove(NewArmor->GetArmorType());
			NewArmor->Destroy();
			SetStatus();
			return;
		}
		else if (NewArmor->GetArmorType() == Armor.Key)
		{
			Armor.Value->UnEquip();
			Armors.Add(NewArmor->GetArmorType(), NewArmor);
			NewArmor->Equip(OwnerCharacter);
			SetStatus();
			return;
		}
	}
	Armors.Add(NewArmor->GetArmorType(), NewArmor);
	NewArmor->Equip(OwnerCharacter);
	SetStatus();
	
}

void UCEquipComponent::SetStatus()
{
	EquipStatus = {};
	for (TPair<EArmorType, ACArmor*> Armor : Armors)
	{
		if (!!Armor.Value)
		{
			EquipStatus += Armor.Value->GetStatusData();
		}
		else
		{
			EquipStatus += {};
		}
	}
	if (SetNewStatus.IsBound())
	{
		SetNewStatus.Broadcast(EquipStatus);
	}
}

