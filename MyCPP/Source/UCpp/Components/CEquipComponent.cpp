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

	NewArmor= OwnerCharacter->GetWorld()->SpawnActorDeferred<ACArmor>(NewArmorClass, transform, OwnerCharacter);
	UGameplayStatics::FinishSpawningActor(NewArmor, transform);

	CheckNull(NewArmor);

	//NewArmor->GetArmorType();
	
	for (TPair<EArmorType, ACArmor*> Armor : Armors)
	{
		if (Armor.Value->GetClass() == NewArmorClass)
		{
			Armor.Value->Detach();
			if (Armor.Value->GetArmorType() == EArmorType::Shield)
			{
				if (OffShield.IsBound())
				{
					OffShield.Broadcast(Armor.Value);
				}
			}
			Armors.Remove(NewArmor->GetArmorType());
			NewArmor->Destroy();
			SetStatus();
			return;
		}
		else if (NewArmor->GetArmorType() == Armor.Key)
		{
			Armor.Value->Detach();
			if (Armor.Value->GetArmorType() == EArmorType::Shield)
			{
				if (OffShield.IsBound())
				{
					OffShield.Broadcast(Armor.Value);
				}
			}
			Armors.Add(NewArmor->GetArmorType(), NewArmor);
			NewArmor->Attach();
			SetStatus();
			return;
		}
	}
	Armors.Add(NewArmor->GetArmorType(), NewArmor);
	if (NewArmor->GetArmorType() == EArmorType::Shield)
	{
		if (OnShield.IsBound())
		{
			OnShield.Broadcast(NewArmor);
		}
	}
	NewArmor->Attach();
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

void UCEquipComponent::OnSecondEquip(EArmorType InArmorType)
{
	switch (InArmorType)
	{
	case EArmorType::Shield:
		if (!(!Armors.Find(EArmorType::Shield) || !!!Armors[EArmorType::Shield]))
		{
			Armors[EArmorType::Shield]->MoveTo("Socket_Shield");
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
			Armors[EArmorType::Shield]->MoveTo("Holster_Shield");
		}
		break;
	}
}

