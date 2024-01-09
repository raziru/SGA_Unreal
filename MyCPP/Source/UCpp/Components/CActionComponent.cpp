// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CActionComponent.h"
#include "Global.h"
#include "Actions/CActionData.h"
#include "Actions/CAttachment.h"
#include "Actions/CEquipment.h"
#include "Actions/CDoAction.h"
#include "Characters/CPlayer.h"
#include "Widgets/Action/CUserWidget_ActionList.h"

// Sets default values for this component's properties
UCActionComponent::UCActionComponent()
{
	CHelpers::GetClass<UCUserWidget_ActionList>(&ActionListClass, "WidgetBlueprint'/Game/Widgets/Action/WB_ActionList.WB_ActionList_C'");
	CHelpers::GetAsset<UCActionData>(&UnarmedData, "CActionData'/Game/Actions/DataAsset/DA_Unarmed.DA_Unarmed'");
	Datas[(int32)EActionType::Unarmed] = UnarmedData;

}


// Called when the game starts
void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());

	//ACharacter* Owner = Cast<ACharacter>(GetOwner());
	for (int32 i = 0; i < (int32)EActionType::Max; i++)
	{
		if (!!Datas[i])
		{
			ActionBeginPlay(Datas[i]);
		}
	}

	Player = Cast<ACPlayer>(GetOwner());
	if (!!Player)
	{
		ActionList = CreateWidget<UCUserWidget_ActionList, APlayerController>(Owner->GetController<APlayerController>(), ActionListClass);
		ActionList->AddToViewport();
		ActionList->SetVisibility(ESlateVisibility::Hidden);
	}
	

	IICharacter* Character = Cast<IICharacter>(GetOwner());
	CheckNull(Character);
	Character->OnDefaultMode();
	
}
void UCActionComponent::SetUnarmedMode()
{
	if (!!Datas[(int32)Type])
	{
		ACEquipment* equipment = Datas[(int32)Type]->GetEquipment();
		CheckNull(equipment);

		equipment->Unequip();
	}

	CheckNull(Datas[(int32)EActionType::Unarmed]);
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

void UCActionComponent::SetMainWeaponMode()
{
	if (!!MainWeaponData)
	{
		CLog::Print((int32)MainWeaponType);
		CLog::Print(Datas[(int32)MainWeaponType]->GetName());
		SetMode(MainWeaponType);
	}
	else
	{
		SetFistMode();
	}

}

void UCActionComponent::SetSecondWeaponMode()
{
}

void UCActionComponent::SetToolMode()
{
	//SetMode(EActionType::Tool);
	if (!!Datas[(int32)EActionType::Tool])
	{
		PrevType = Type;
		SetMode(EActionType::Tool);		
		DoAction();
	}
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

void UCActionComponent::SetNewMainWeapon(class UCActionData* NewItemAction, EActionType NewItemActionType)
{
	CheckNull(NewItemAction);
	if (this->MainWeaponData == NewItemAction && this->MainWeaponType == NewItemActionType)
	{
		CLog::Print("SameThing");
		this->MainWeaponData->DataDestroy();
		this->MainWeaponData = nullptr;
		this->MainWeaponType = EActionType::Max;
	}
	else
	{
		//SetUnarmedMode();
		Datas[(int32)NewItemActionType]->DataDestroy();
		//Datas[(int32)NewItemActionType] = nullptr;
		this->MainWeaponData = NewItemAction;

		ActionBeginPlay(NewItemAction);
		this->MainWeaponType = NewItemActionType;
		Datas[(int32)NewItemActionType] = NewItemAction;
	}
	

}

void UCActionComponent::SetNewSecondWeapon(UCActionData* NewItemAction, EActionType NewItemActionType)
{
}

void UCActionComponent::SetNewTool(UCActionData* NewToolAction, bool IsConsumable)
{
	if (Datas[(int32)EActionType::Tool] == NewToolAction)
	{
		CLog::Print("SameThing");
		Datas[(int32)EActionType::Tool]->DataDestroy();
		Datas[(int32)EActionType::Tool] = nullptr;
	}
	else
	{
		if (!!ToolAction)
		{
			Datas[(int32)EActionType::Tool]->DataDestroy();
		}
		Datas[(int32)EActionType::Tool] = NewToolAction;
		ActionBeginPlay(Datas[(int32)EActionType::Tool]);
		Datas[(int32)EActionType::Tool]->GetDoAction()->EndAction.AddDynamic(this, &UCActionComponent::EndTool);
		IsConsumableTool = IsConsumable;
	}
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

void UCActionComponent::OnViewActionList()
{
	if (!!Player)
	{
		ActionList->SetVisibility(ESlateVisibility::Visible);

		Player->GetController<APlayerController>()->bShowMouseCursor = true;
		Player->GetController<APlayerController>()->SetInputMode(FInputModeGameAndUI());//마우스를 받는 상태가 됨

		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.000100f);//시간 배율 변경
	}
	
	

}

void UCActionComponent::OffViewActionList()
{
	if (!!Player)
	{
		ActionList->SetVisibility(ESlateVisibility::Hidden);

		Player->GetController<APlayerController>()->bShowMouseCursor = false;
		Player->GetController<APlayerController>()->SetInputMode(FInputModeGameOnly());

		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
	}
	
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

void UCActionComponent::OnSecondEquip()
{
	
	if (EquipSecond.IsBound())
	{
		EquipSecond.Broadcast(Type);
	}
	
}

void UCActionComponent::OffSecondEquip()
{
	if (UnequipSecond.IsBound())
	{
		UnequipSecond.Broadcast(Type);
	}
}


void UCActionComponent::EndTool()
{
	SetMode(PrevType);
	if (EndToolAction.IsBound())
	{
		EndToolAction.Broadcast();
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
	CLog::Print("CheckEquip");

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

void UCActionComponent::ActionBeginPlay(UCActionData* NewAction)
{
	NewAction->BeginPlay(Owner);
	NewAction->GetDoAction()->ActionPress.AddDynamic(this, &UCActionComponent::ActionPress);
	//NewAction->GetDoAction()->EndAction.AddDynamic(this, )
	NewAction->GetEquipment()->OnEquipmentDelegate.AddDynamic(this, &UCActionComponent::OnSecondEquip);
	NewAction->GetEquipment()->OnUnequipmentDelegate.AddDynamic(this, &UCActionComponent::OffSecondEquip);
}


