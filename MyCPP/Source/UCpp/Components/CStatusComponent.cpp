// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CStatusComponent.h"
#include "Global.h"

UCStatusComponent::UCStatusComponent()
{

}

void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}

void UCStatusComponent::AddHealth(float InAmount)
{
	Health += InAmount;

	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
}

void UCStatusComponent::SubHealth(float InAmount)
{
	Health -= InAmount;

	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
}

void UCStatusComponent::SetMove()
{
	bCanMove = true;
}

void UCStatusComponent::SetStop()
{
	bCanMove = false;
}

void UCStatusComponent::AddStatus(const FStatusData NewStatus)
{
	this->MaxHealth   += NewStatus.MaxHealth;
	this->WalkSpeed   += NewStatus.WalkSpeed;
	this->RunSpeed    += NewStatus.RunSpeed;
	this->SprintSpeed += NewStatus.SprintSpeed;


	if (RefreshStatus.IsBound())
	{
		RefreshStatus.Broadcast();
	}
}

void UCStatusComponent::SubStatus(const FStatusData NewStatus)
{
	this->MaxHealth   -= NewStatus.MaxHealth;
	this->WalkSpeed   -= NewStatus.WalkSpeed;
	this->RunSpeed    -= NewStatus.RunSpeed;
	this->SprintSpeed -= NewStatus.SprintSpeed;

	if (RefreshStatus.IsBound())
	{
		RefreshStatus.Broadcast();
	}
}






