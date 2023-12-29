	// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CActionComponent.h"
#include "Global.h"
#include "Actions/CActionData.h"
#include "Actions/CAttachment.h"
#include "Actions/CEquipment.h"
#include "Actions/CDoAction.h"
#include "GameFramework/Character.h"
// Sets default values for this component's properties
UCActionComponent::UCActionComponent()
{
	
}


// Called when the game starts
void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* character = Cast<ACharacter>(GetOwner());
	for (int32 i = 0; i < (int32)EActionType::Max; i++)
	{
		if (!!Datas[i])
		{
			Datas[i]->BeginPlay(character);
			Datas[i]->GetDoAction()->ActionPress.AddDynamic(this, &UCActionComponent::ActionPress);
		}
	}
	
	
}
void UCActionComponent::SetUnarmedMode()
{
	if (!!Datas[(int32)Type])
	{
		ACEquipment* equipment = Datas[(int32)Type]->GetEquipment();
		CheckNull(equipment);

		equipment->Unequip();
	}

	ACEquipment* equipment = Datas[(int32)EActionType::Unarmed]->GetEquipment();
	CheckNull(equipment);

	equipment->Equip();

	ChangeType(EActionType::Unarmed);
}
void UCActionComponent::SetFistMode()
{
	SetMode(EActionType::Fist);

}
void UCActionComponent::SetOneHandMode()
{
	SetMode(EActionType::OneHand);

}

void UCActionComponent::SetTwoHandMode()
{
	SetMode(EActionType::TwoHand);

}

void UCActionComponent::SetWarpMode()
{
	SetMode(EActionType::Warp);
}

void UCActionComponent::SetFireStormMode()
{
	SetMode(EActionType::FireStorm);
}

void UCActionComponent::SetThrowMode()
{
	SetMode(EActionType::Throw);
}

void UCActionComponent::SetItemTypeMode()
{
	if (!!ItemTypeData)
	{
		SetMode(ItemActionType);
	}
	else
	{
		SetFistMode();
	}

}

void UCActionComponent::SetSecondItemTypeMode()
{
}

void UCActionComponent::OffAllCollision()
{
	for (UCActionData* data : Datas)
	{
		if (!!data == false)
			continue;

		if (!!data->GetAttachment() == false)
			continue;

		data->GetAttachment()->OffCollision();
	}
}

void UCActionComponent::SetNewAction(class UCActionData* NewItemAction, EActionType NewItemActionType)
{
	if (this->ItemTypeData == NewItemAction && this->ItemActionType == NewItemActionType)
	{
		this->ItemTypeData   = Datas[(int32)EActionType::Unarmed];
		this->ItemActionType = EActionType::Unarmed;
	}
	else
	{
		this->ItemTypeData = NewItemAction;
		this->ItemActionType = NewItemActionType;
	}
	
	Datas[(int32)NewItemActionType] = NewItemAction;

}

void UCActionComponent::SetNewSecondAction(UCActionData* NewItemAction, EActionType NewItemActionType)
{
}

void UCActionComponent::DoAction()
{
	CheckTrue(IsUnarmedMode());

	if (!!Datas[(int32)Type])
	{
		ACDoAction* action = Datas[(int32)Type]->GetDoAction();

		if (!!action)
			action->DoAction();
	}
}

void UCActionComponent::DoActionRelease()
{
	CheckTrue(IsUnarmedMode());

	if (!!Datas[(int32)Type])
	{
		ACDoAction* action = Datas[(int32)Type]->GetDoAction();

		if (!!action)
			action->DoActionRelease();
	}
}

void UCActionComponent::DoSecondAction()
{
	CheckTrue(IsUnarmedMode());

	if (!!Datas[(int32)Type])
	{
		ACDoAction* action = Datas[(int32)Type]->GetDoAction();

		if (!!action)
			action->DoSecondAction();
	}
	CLog::Print(OnShield);
}

void UCActionComponent::DoSecondActionRelease()
{
	CheckTrue(IsUnarmedMode());

	if (!!Datas[(int32)Type])
	{
		ACDoAction* action = Datas[(int32)Type]->GetDoAction();

		if (!!action)
			action->DoSecondActionRelease();
	}
}

void UCActionComponent::DoAim()
{
	if (IsAiming)
	{
		OffAim();
	}
	else
	{
		OnAim();
	}
}

void UCActionComponent::OnAim()
{
	SetAimMode(true);
}

void UCActionComponent::OffAim()
{
	SetAimMode(false);
}

void UCActionComponent::SetAimMode(bool InAim)
{
	CheckTrue(IsUnarmedMode());

	if (!!Datas[(int32)Type])
	{
		ACDoAction* action = Datas[(int32)Type]->GetDoAction();

		if (!!action)
			InAim ? action->OnAim() : action->OffAim();
	}
}

void UCActionComponent::ActionPress(bool InPressAction, bool InPressSecondAction)
{
	if (OnActionPress.IsBound())
	{
		OnActionPress.Broadcast(InPressAction, InPressSecondAction, OnShield);
	}
}


void UCActionComponent::SetMode(EActionType InType)
{
	if (Type == InType)//같은 무기 일때 해제
	{
		SetUnarmedMode();

		return;
	}
	else if (IsUnarmedMode() == false)//다른무기 장착
	{
		ACEquipment* equipment = Datas[(int32)Type]->GetEquipment();
		CheckNull(equipment);

		equipment->Unequip();
	}

	ACEquipment* equipment = Datas[(int32)InType]->GetEquipment();
	CheckNull(equipment);

	equipment->Equip();

	ChangeType(InType);


}

void UCActionComponent::ChangeType(EActionType InNewType)
{
	EActionType prevType = InNewType;
	Type = InNewType;

	if (OnActionTypeChanged.IsBound())
		OnActionTypeChanged.Broadcast(prevType, InNewType);
	//delegate에 AddDynamic으로 저장된 모든 함수를 한번에 실행한다.
}


