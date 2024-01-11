// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CStatusComponent.h"
#include "Global.h"

UCStatusComponent::UCStatusComponent()
{

}

void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentStatus += DefaultStatus;
	Health = CurrentStatus.MaxHealth;
	Mana = CurrentStatus.MaxMana;
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

void UCStatusComponent::SetMove()
{
	bCanMove = true;
}

void UCStatusComponent::SetStop()
{
	bCanMove = false;
}


void UCStatusComponent::SetNewStatus(const FStatusData NewStatus)
{
	CurrentStatus = DefaultStatus + NewStatus;

	if (RefreshStatus.IsBound())
	{
		RefreshStatus.Broadcast(CurrentStatus);
	}
}







