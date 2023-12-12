

#include "Interact/CInteract.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/ShapeComponent.h"
#include "IInteract.h"

// Sets default values
ACInteract::ACInteract()
{

}

void ACInteract::AttachToCollision(UShapeComponent* InComponent, FName InSocketName)
{
	CLog::Log(InComponent->GetName());
	InComponent->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

void ACInteract::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	
	Super::BeginPlay();
	GetComponents<UShapeComponent>(Interactions);
	for (UShapeComponent* Interact : Interactions)
	{
		Interact->OnComponentBeginOverlap.AddDynamic(this, &ACInteract::OnComponentBeginOverlap);
		Interact->OnComponentEndOverlap.AddDynamic(this,   &ACInteract::OnComponentEndOverlap);
	}
}

void ACInteract::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OwnerCharacter == OtherActor);
	CheckTrue(OtherActor->GetClass() == OwnerCharacter->GetClass());
	if (OnInteractBeginOverlap.IsBound())
		OnInteractBeginOverlap.Broadcast(OtherActor);

}

void ACInteract::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckTrue(OwnerCharacter == OtherActor);
	CheckTrue(OtherActor->GetClass() == OwnerCharacter->GetClass());
	if (OnInteractEndOverlap.IsBound())
		OnInteractEndOverlap.Broadcast(OtherActor);
}


