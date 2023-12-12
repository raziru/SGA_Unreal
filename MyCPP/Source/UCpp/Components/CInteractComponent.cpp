// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CInteractComponent.h"
#include "Global.h"
#include "Interact/CInteract.h"
#include "Interact/IInteract.h"
#include "GameFramework/Character.h"
#include "Components/ShapeComponent.h"


UCInteractComponent::UCInteractComponent()
{
	
}


void UCInteractComponent::Interact()
{
	if (InteractArray.Num()>0)
	{
		IIInteract* Interacted = InteractArray[0];

		Interacted->Interact();
	}
}

void UCInteractComponent::OnInteractBeginOverlap(AActor* InInteracted)
{
	IIInteract* Interacted = Cast<IIInteract>(InInteracted);
	CheckNull(Interacted);

	CLog::Print(InInteracted->GetName());

	InteractArray.AddUnique(Interacted);
}

void UCInteractComponent::OnInteractEndOverlap(AActor* InInteracted)
{
	IIInteract* Interacted = Cast<IIInteract>(InInteracted);
	CheckNull(Interacted);

	InteractArray.Remove(Interacted);
}

// Called when the game starts
void UCInteractComponent::BeginPlay()
{
	

	Super::BeginPlay();

	
}




