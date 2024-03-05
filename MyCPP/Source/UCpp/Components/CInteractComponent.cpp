// Fill out your copyright notice in the Description page of Project Settings.


#include "CInteractComponent.h"
#include "Global.h"
#include "Interact/IInteract.h"
#include "Components/ShapeComponent.h"
#include "Widgets/CUserWidget_Interact.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"


UCInteractComponent::UCInteractComponent()
{
	CHelpers::GetClass<UCUserWidget_Interact>(&InteractClass, "WidgetBlueprint'/Game/Widgets/WB_Interact.WB_Interact_C'");

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

	if (Interacted->GetInteractType() == EInteractType::Disabled)
	{
		return;
	}

	InteractArray.AddUnique(Interacted);
	
	UpdateWidget();
}

void UCInteractComponent::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IIInteract* Interacted = Cast<IIInteract>(OtherActor);
	CheckNull(Interacted);

	/*if (Interacted->GetInteractType() == EInteractType::Disabled)
	{
		return;
	}*/

	InteractArray.Remove(Interacted);
	UpdateWidget();

}

void UCInteractComponent::UpdateWidget()
{
	
	if (!!!InteractWidget)
	{
		InteractWidget = Cast<UCUserWidget_Interact>(CreateWidget(GetWorld(), InteractClass));
		//CheckNull(InteractWidget);
		InteractWidget->AddToViewport();
		InteractWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	
	if (InteractArray.Num()<=0)
	{
		InteractWidget->SetVisibility(ESlateVisibility::Hidden);

	}
	else
	{
		FString string;
		switch (InteractArray[0]->GetInteractType())
		{
		case EInteractType::Openable:
			string = "Open";
			break;

		case EInteractType::Pickable:
			string = "PickUp";
			break;

		case EInteractType::Speakable:
			string = "Speak";
			break;

		case EInteractType::Disabled:
			string = "None";
		default:
			break;

		}

		InteractWidget->Update((Cast<AActor>(InteractArray[0])->GetName()), string);
		InteractWidget->SetVisibility(ESlateVisibility::Visible);
	}
}





