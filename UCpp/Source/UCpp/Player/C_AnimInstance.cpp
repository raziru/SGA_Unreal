// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/C_AnimInstance.h"
#include "Weapons/CRifle.h"
#include "Interface/IRifle.h"
#include "Global.h"
#include "GameFramework/Character.h"

void UC_AnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UC_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(OwnerCharacter);

	Speed = OwnerCharacter->GetVelocity().Size2D();
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());
	Pitch = OwnerCharacter->GetBaseAimRotation().Pitch;

	IIRifle* rifle = Cast<IIRifle>(OwnerCharacter);
	if (!!rifle)
	{
		bEquipped = rifle->GetRifle()->GetEquipped();
		//bAiming = rifle->GetRifle()->GetAiming();
	}
}
