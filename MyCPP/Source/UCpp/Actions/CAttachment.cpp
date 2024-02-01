// Fill out your copyright notice in the Description page of Project Settings.


#include "CAttachment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ShapeComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CActionComponent.h"



// Sets default values
ACAttachment::ACAttachment()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");

}



// Called when the game starts or when spawned
void ACAttachment::BeginPlay()
{
	//�� ��忡 �Լ��� ����� ��� ����� �Լ��� Super::BeginPlay()���� ����ǰ� �̾ �ۼ��� �ڵ���� ����ȴ�.
	//�׷��� ���� �Ҵ��� �����ϰ� �θ��Լ��� ȣ���ؾ� null������ �߻����� �ʴ´�.
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	Status = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
	Action = CHelpers::GetComponent<UCActionComponent>(OwnerCharacter);
	Super::BeginPlay();

	Action->OnActionPress.AddDynamic(this, &ACAttachment::OnPress);
	GetComponents<UShapeComponent>(ShapeComponents);
	for (UShapeComponent* component : ShapeComponents)
	{
		component->OnComponentBeginOverlap.AddDynamic(this, &ACAttachment::OnComponentBeginOverlap);
		component->OnComponentEndOverlap.AddDynamic(this, &ACAttachment::OnComponentEndOverlap);
	}
	OffCollision();
	
}


void ACAttachment::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OwnerCharacter == OtherActor);
	CheckTrue(OtherActor->GetClass() == OwnerCharacter->GetClass());

	if (OnAttachmentBeginOverlap.IsBound())
		OnAttachmentBeginOverlap.Broadcast(OwnerCharacter, this, Cast<ACharacter>(OtherActor));
}

void ACAttachment::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OnAttachmentEndOverlap.IsBound())
		OnAttachmentEndOverlap.Broadcast(OwnerCharacter, this, Cast<ACharacter>(OtherActor));
}

void ACAttachment::OnPress(bool InPressAction, bool InPressSecondAction)
{
	if (InPressAction)
	{
		IsPress = true;
	}
	else
	{
		IsPress = false;
	}

	if (InPressSecondAction)
	{
		IsRightPress = true;
	}
	else
	{
		IsRightPress = false;
	}
}

void ACAttachment::OnCollision()
{
	for (UShapeComponent* component : ShapeComponents)
		component->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	if (OnAttachmentCollision.IsBound())
		OnAttachmentCollision.Broadcast();
}

void ACAttachment::OffCollision()
{
	for (UShapeComponent* component : ShapeComponents)
		component->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (OffAttachmentCollision.IsBound())
		OffAttachmentCollision.Broadcast();
}
void ACAttachment::AttachTo(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

void ACAttachment::AttachToCollision(UShapeComponent* InComponent, FName InSocketName)
{
	CLog::Log(InComponent->GetName());
	InComponent->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

