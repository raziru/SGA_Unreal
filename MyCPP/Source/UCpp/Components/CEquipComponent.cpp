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

	FTransform transform;

	//NewArmor = Cast<ACArmor>(OwnerCharacter->GetWorld()->SpawnActor(NewArmorClass));

	NewArmor= OwnerCharacter->GetWorld()->SpawnActorDeferred<ACArmor>(NewArmorClass, transform, OwnerCharacter);
	UGameplayStatics::FinishSpawningActor(NewArmor, transform);

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
			NewArmor->Equip();
			SetStatus();
			return;
		}
	}
	Armors.Add(NewArmor->GetArmorType(), NewArmor);
	NewArmor->Equip();
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


	if (!Armors.Find(EArmorType::Shield) || !!!Armors[EArmorType::Shield])
	{
		if (OnShield.IsBound())
		{
			OnShield.Broadcast(false);
		}
	}
	else
	{
		if (OnShield.IsBound())
		{
			OnShield.Broadcast(true);
		}
	}
}

void UCEquipComponent::OnSecondEquip(EArmorType InArmorType)
{
	switch (InArmorType)
	{
	case EArmorType::Shield:
		if (!(!Armors.Find(EArmorType::Shield) || !!!Armors[EArmorType::Shield]))
		{
			Armors[EArmorType::Shield]->AttachTo("Socket_Shield");
		}
		break;
	}
}

void UCEquipComponent::OnSecondUnEquip(EArmorType InArmorType)
{
	switch (InArmorType)
	{

	case EArmorType::Shield:
		if (!(!Armors.Find(EArmorType::Shield) || !!!Armors[EArmorType::Shield]))
		{
			Armors[EArmorType::Shield]->AttachTo("Holster_Shield");
		}
		break;
	}
}

