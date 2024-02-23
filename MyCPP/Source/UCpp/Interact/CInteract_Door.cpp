// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact/CInteract_Door.h"
#include "Global.h"


ACInteract_Door::ACInteract_Door()
{
	InteractType = EInteractType::Openable;
	//CHelpers::CreateComponent<UStaticMeshComponent>(this, &Door, "Door");
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &DoorFrame, "DoorFrame");

}

void ACInteract_Door::BeginPlay()
{
	Super::BeginPlay();
}

void ACInteract_Door::Interact(AActor* InOther)
{
	Super::Interact(InOther);
	if (IsOpened)
	{
		Close();
		IsOpened = false;
	}
	else
	{
		Open();
		IsOpened = true;
	}
}


