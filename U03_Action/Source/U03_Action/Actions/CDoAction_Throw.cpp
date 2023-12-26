
#include "CDoAction_Throw.h"
#include "Global.h"
#include "CAim.h"
//#include "CThrow.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

void ACDoAction_Throw::BeginPlay()
{
	Super::BeginPlay();

	Aim = NewObject<UCAim>();//Unreal Gabarge 컬렉터에서 인식하게 만들기 위함

	Aim->BeginPlay(OwnerCharacter);
	//Aim->ConditionalFinishDestroy();
}

void ACDoAction_Throw::DoAction()
{
	CheckFalse(State->IsIdleMode());
	State->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRatio, Datas[0].StartSection);
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Throw::Begin_DoAction()
{

}

void ACDoAction_Throw::End_DoAction()
{
	State->SetIdleMode();
	Status->SetMove();
}

void ACDoAction_Throw::OnAim()
{
	Aim->OnZoom();
}

void ACDoAction_Throw::OffAim()
{
	Aim->OffZoom();
}

void ACDoAction_Throw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Aim->Tick(DeltaTime);
}

void ACDoAction_Throw::OnThrowBeginOverlap(FHitResult InHitResult)
{

}
