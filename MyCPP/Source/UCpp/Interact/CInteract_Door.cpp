// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact/CInteract_Door.h"
#include "Global.h"


ACInteract_Door::ACInteract_Door()
{
	InteractType = EInteractType::Openable;
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Door, "Door");
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &DoorFrame, "DoorFrame");
	//CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");

	//Scene->SetupAttachment(RootComponent);
	//DoorFrame->AttachToComponent(Scene, FAttachmentTransformRules::KeepRelativeTransform);
	DoorFrame->SetupAttachment(RootComponent);
	Door->AttachToComponent(DoorFrame, FAttachmentTransformRules::KeepRelativeTransform);
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


