// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CAnimInstance.h"
#include "Global.h"
#include "Components/CActionComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(character);

	Speed = character->GetVelocity().Size2D();
	Direction = CalculateDirection(character->GetVelocity(), character->GetControlRotation());
	Pitch = character->GetBaseAimRotation().Pitch;
	isFalling = character->GetCharacterMovement()->IsFalling();

	UCActionComponent* action = CHelpers::GetComponent<UCActionComponent>(character);
	CheckNull(action);

	action->OnActionTypeChanged.AddDynamic(this, &UCAnimInstance::OnActionTypeChanged);
	action->OnActionPress.AddDynamic(this, &UCAnimInstance::OnActionPress);
	action->OnSecondHand.AddDynamic(this, &UCAnimInstance::OnSecondHand);

	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(character);
	if (!!state)
	{
		IsDead = state->IsDeadMode();
	}

	UCFeetComponent* feet = CHelpers::GetComponent<UCFeetComponent>(character);
	if (!!feet)
		FeetData = feet->GetData();
}


void UCAnimInstance::OnActionTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	ActionType = InNewType;
}

void UCAnimInstance::OnActionPress(bool InPressAction, bool InPressSecondAction)
{
	PressAction = InPressAction;
	PressSecondAction = InPressSecondAction;
}

void UCAnimInstance::OnSecondHand(bool InSecondHand)
{
	SecondHand = InSecondHand;
}




