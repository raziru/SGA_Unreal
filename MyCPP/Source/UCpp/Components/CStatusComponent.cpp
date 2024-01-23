// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CStatusComponent.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"

UCStatusComponent::UCStatusComponent()
{

}

void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentStatus += DefaultStatus;
	Health = CurrentStatus.MaxHealth-10;
	Mana = CurrentStatus.MaxMana-10;
}

void UCStatusComponent::AddHealth(float InAmount)
{
	Health += InAmount;

	Health = FMath::Clamp(Health, 0.0f, CurrentStatus.MaxHealth);
}

void UCStatusComponent::SubHealth(float InAmount)
{
	Health -= InAmount;

	Health = FMath::Clamp(Health, 0.0f, CurrentStatus.MaxHealth);
}

void UCStatusComponent::AddMana(float InAmount)
{
	Mana += InAmount;

	Mana = FMath::Clamp(Health, 0.0f, CurrentStatus.MaxMana);
}

void UCStatusComponent::SubMana(float InAmount)
{
	Mana -= InAmount;

	Mana = FMath::Clamp(Health, 0.0f, CurrentStatus.MaxMana);
}


void UCStatusComponent::SetMove()
{
	bCanMove = true;
}

void UCStatusComponent::SetStop()
{
	bCanMove = false;
}

void UCStatusComponent::SetSpeed(ECharacterSpeed InType)
{
	UCharacterMovementComponent* movement = CHelpers::GetComponent<UCharacterMovementComponent>(GetOwner());

	movement->MaxWalkSpeed = CurrentStatus.Speed[(int32)InType];
	CurrentStatus.CurrentSpeed = InType;
}


void UCStatusComponent::SetNewStatus(const FStatusData NewStatus)
{
	CurrentStatus = DefaultStatus + NewStatus;

	if (RefreshStatus.IsBound())
	{
		RefreshStatus.Broadcast(CurrentStatus);
	}
	SetSpeed(CurrentStatus.CurrentSpeed);
}







