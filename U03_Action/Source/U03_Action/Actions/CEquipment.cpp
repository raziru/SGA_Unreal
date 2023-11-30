// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/CEquipment.h"
#include "Global.h"
#include "Characters/ICharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"


ACEquipment::ACEquipment()
{

}

void ACEquipment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	Status = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
	Super::BeginPlay();
}

void ACEquipment::Equip_Implementation()
{
	State->SetEquipMode();

	if (Data.AnimMontage != NULL)
		OwnerCharacter->PlayAnimMontage(Data.AnimMontage, Data.PlayRatio, Data.StartSection);
	else
		End_Equip();

	OwnerCharacter->bUseControllerRotationYaw = true;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;

	IICharacter* character = Cast<IICharacter>(OwnerCharacter);
	CheckNull(character);

	character->ChangeColor(Color);
}

void ACEquipment::Begin_Equip_Implementation()
{
	//F12로 따라가지 못하는 것이기 때문에 외부에 연결된 함수를 다른 클래스에서 찾아비교해야 한다.
	if (OnEquipmentDelegate.IsBound())
		OnEquipmentDelegate.Broadcast();
}

void ACEquipment::End_Equip_Implementation()
{
	bEquipped = true;
	State->SetIdleMode();
}

void ACEquipment::Unequip_Implementation()
{
	bEquipped = false;
	

	if (OnUnequipmentDelegate.IsBound())
		OnUnequipmentDelegate.Broadcast();

	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
}