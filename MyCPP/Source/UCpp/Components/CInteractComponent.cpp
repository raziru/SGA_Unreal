// Fill out your copyright notice in the Description page of Project Settings.


#include "CInteractComponent.h"
#include "Global.h"
#include "Interact/IInteract.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/Character.h"


UCInteractComponent::UCInteractComponent()
{

}

void UCInteractComponent::BeginPlay()
{
	
	ACharacter* character = Cast<ACharacter>(GetOwner());
	
	Super::BeginPlay();

	character->GetComponents<UShapeComponent>(InteractBox);

	for (UShapeComponent* component : InteractBox)
	{
		if (component->GetName()=="InteractBox")
		{
			component->OnComponentBeginOverlap.AddDynamic(this, &UCInteractComponent::OnComponentBeginOverlap);
			component->OnComponentEndOverlap.AddDynamic(this,   &UCInteractComponent::OnComponentEndOverlap);
			break;
		}
		
	}


}


void UCInteractComponent::Interact()
{
	if (InteractArray.Num() > 0)
	{
		IIInteract* Interacted = InteractArray[0];

		Interacted->Interact(GetOwner());
	}
}

void UCInteractComponent::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IIInteract* Interacted = Cast<IIInteract>(OtherActor);
	CheckNull(Interacted);

	CLog::Print(OtherActor->GetName());

	InteractArray.AddUnique(Interacted);
}

void UCInteractComponent::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IIInteract* Interacted = Cast<IIInteract>(OtherActor);
	CheckNull(Interacted);

	InteractArray.Remove(Interacted);
}





