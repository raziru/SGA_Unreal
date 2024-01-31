// Fill out your copyright notice in the Description page of Project Settings.


#include "CStaticArmor.h"
#include "Global.h"
#include "GameFramework/Character.h"


ACStaticArmor::ACStaticArmor()
{
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh");

}

void ACStaticArmor::Attachment()
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

void ACStaticArmor::MoveTo(FName InSocket)
{
	if (OnSocket == false)
	{
		AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocket);
		OnSocket = true;
	}
	else
	{
		AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), SocketName);
		OnSocket = false;

	}
}

