// Fill out your copyright notice in the Description page of Project Settings.


#include "CDoAction_Throw.h"
#include "Global.h"
#include "Actions/CAim.h"
#include "CThrow.h"
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

	/*if (Aim->IsAvaliable())
		CheckFalse(Aim->IsZoom());*/

	CheckFalse(State->IsIdleMode());
	State->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRatio, Datas[0].StartSection);
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Throw::Begin_DoAction()
{
	FVector location = OwnerCharacter->GetMesh()->GetSocketLocation("Hand_Throw_Projectile");
	FRotator rotator = OwnerCharacter->GetController()->GetControlRotation();

	FTransform transform = Datas[0].EffectTransform;
	transform.AddToTranslation(location);
	transform.SetRotation(FQuat(rotator));

	ACThrow* throwObject = OwnerCharacter->GetWorld()->SpawnActorDeferred<ACThrow>(Datas[0].ThrowClass, transform, OwnerCharacter, NULL, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	throwObject->OnThrowBeginOverlap.AddDynamic(this, &ACDoAction_Throw::OnThrowBeginOverlap);
	UGameplayStatics::FinishSpawningActor(throwObject, transform);//지연 생성으로 add dynamic을 할때 null참조하는 것을 막기 위함
}

void ACDoAction_Throw::End_DoAction()
{
	State->SetIdleMode();
	Status->SetMove();
}

void ACDoAction_Throw::DoSecondAction()
{
	OnAim();
}

void ACDoAction_Throw::DoSecondActionRelease()
{
	OffAim();
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
	FDamageEvent e;
	InHitResult.GetActor()->TakeDamage(Datas[0].Power, e, OwnerCharacter->GetController(), this);
}

