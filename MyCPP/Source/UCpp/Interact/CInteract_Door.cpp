// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact/CInteract_Door.h"
#include "Global.h"
#include "Components/BoxComponent.h"

ACInteract_Door::ACInteract_Door()
{
	InteractType = EInteractType::Openable;
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Door, "Door");
	CHelpers::CreateComponent<UBoxComponent>(this, &DoorProxVolume, "DoorProxVolume");
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &DoorFrame, "DoorFrame");
	
	DoorFrame->SetupAttachment(RootComponent);
	Door->AttachToComponent(DoorFrame, FAttachmentTransformRules::KeepRelativeTransform);
	DoorProxVolume->AttachToComponent(Door, FAttachmentTransformRules::KeepRelativeTransform);
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


