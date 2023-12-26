// Fill out your copyright notice in the Description page of Project Settings.


#include "CStaticArmor.h"
#include "Global.h"
#include "GameFramework/Character.h"


ACStaticArmor::ACStaticArmor()
{
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh");

}

void ACStaticArmor::Attachment(ACharacter* OwnerCharacter)
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), SocketName);

	if (OnAttachmentDelegate.IsBound())
	{
		OnAttachmentDelegate.Broadcast(StatusData);
	}
}

void ACStaticArmor::Detachment()
{
	DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepRelative, true));
	if (OnDetachmentDelegate.IsBound())
	{
		OnDetachmentDelegate.Broadcast(StatusData);
	}
	Destroy();
}

