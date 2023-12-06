// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/CDoAction_Melee.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Camera/CameraShakeBase.h"

void ACDoAction_Melee::DoAction()
{
	Super::DoAction();

	CheckFalse(Datas.Num() > 0);

	if (bEnable == true)
	{
		bExist = true;
		bEnable = false;

		return;
	}

	CheckFalse(State->IsIdleMode());
	State->SetActionMode();
	const FDoActionData& data = Datas[0];
	OwnerCharacter->PlayAnimMontage(data.AnimMontage, data.PlayRatio, data.StartSection);

	data.bCanMove ? Status->SetMove() : Status->SetStop();

}

void ACDoAction_Melee::Begin_DoAction()
{
	Super::Begin_DoAction();

	CheckFalse(bExist);
	bExist = false;


	OwnerCharacter->StopAnimMontage();

	Index++;

	const FDoActionData& data = Datas[Index];
	OwnerCharacter->PlayAnimMontage(data.AnimMontage, data.PlayRatio, data.StartSection);

	data.bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Melee::End_DoAction()
{
	Super::End_DoAction();

	const FDoActionData& data = Datas[Index];
	OwnerCharacter->StopAnimMontage(data.AnimMontage);

	State->SetIdleMode();
	Status->SetMove();

	Index = 0;
}
void ACDoAction_Melee::OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter)
{//Character ��ü�鸸 ������ �����ȴ�. �׷��� pawn Ŭ������ �Լ��� takeDamage��밡��
	//CLog::Log(InOtherCharacter->GetName());
	//Null üũ�� �־ �߸��� �浹 ����-- fist�� �޷��ִ� �浹ü�� ���� �浹�ϸ鼭 overlap�̶� �ν��ϴ� ��
	CheckNull(InOtherCharacter);
	for (const ACharacter* other : HittedCharacters)
	{
		if (InOtherCharacter == other)
			return;
	}
	HittedCharacters.Add(InOtherCharacter);

	UParticleSystem* hitEffect = Datas[Index].Effect;
	if (!!hitEffect)
	{
		FTransform transform = Datas[Index].EffectTransform;
		transform.AddToTranslation(InOtherCharacter->GetActorLocation());

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitEffect, transform);
	}

	float hitStop = Datas[Index].HitStop;
	if (FMath::IsNearlyZero(hitStop) == false)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1e-3f);//���ߴ� �ð�
		UKismetSystemLibrary::K2_SetTimer(this, "RestoreDilation", hitStop * 1e-3f, false);
		//������ ������ �ð��� ��������
	}

	TSubclassOf<UCameraShakeBase> shake = Datas[Index].ShakeClass;
	if (shake != NULL)
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(shake);

	FDamageEvent e;//�̺�Ʈ�� �䱸�ؼ� ����� �־��ִ� ���̴�.
	InOtherCharacter->TakeDamage(Datas[Index].Power, e, OwnerCharacter->GetController(), this);
}
void ACDoAction_Melee::OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter)
{

}

void ACDoAction_Melee::OnAttachmentCollision()
{

}
void ACDoAction_Melee::OffAttachmentCollision() 
{
	HittedCharacters.Empty();
}

void ACDoAction_Melee::RestoreDilation()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
}