

#include "CDoAction_Bow.h"
#include "Global.h"
#include "Actions/CAim.h"
#include "CThrow.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

void ACDoAction_Bow::BeginPlay()
{
	Super::BeginPlay();

	Aim = NewObject<UCAim>();//Unreal Gabarge 컬렉터에서 인식하게 만들기 위함

	Aim->BeginPlay(OwnerCharacter);
}

void ACDoAction_Bow::DoAction()
{
	PressDoAction = true;

	if (ActionPress.IsBound())
	{
		ActionPress.Broadcast(PressDoAction, PressDoSecondAction);
	}
}

void ACDoAction_Bow::Begin_DoAction()
{

}

void ACDoAction_Bow::End_DoAction()
{
}

void ACDoAction_Bow::DoActionRelease()
{
	PressDoAction = false;

	if (ActionPress.IsBound())
	{
		ActionPress.Broadcast(PressDoAction, PressDoSecondAction);
	}
}

void ACDoAction_Bow::Begin_DoActionRelease()
{
}

void ACDoAction_Bow::End_DoActionRelease()
{
}

void ACDoAction_Bow::DoSecondAction()
{
	OnAim();

}

void ACDoAction_Bow::DoSecondActionRelease()
{
	OffAim();
}

void ACDoAction_Bow::OnAim()
{
	Aim->OnZoom();

}

void ACDoAction_Bow::OffAim()
{
	Aim->OffZoom();

}

void ACDoAction_Bow::Tick(float DeltaTime)
{
	Aim->Tick(DeltaTime);

}

void ACDoAction_Bow::OnThrowBeginOverlap(FHitResult InHitResult)
{
}
