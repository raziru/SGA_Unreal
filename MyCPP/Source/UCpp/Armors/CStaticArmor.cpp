// Fill out your copyright notice in the Description page of Project Settings.


#include "CStaticArmor.h"
#include "Global.h"
#include "GameFramework/Character.h"


ACStaticArmor::ACStaticArmor()
{
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh");

}

void ACStaticArmor::Attach()
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), SocketName);

	if (OnAttach.IsBound())
	{
		OnAttach.Broadcast(StatusData);
	}
}

void ACStaticArmor::Detach()
{
	DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepRelative, true));
	if (OnDetach.IsBound())
	{
		OnDetach.Broadcast(StatusData);
	}
	Destroy();
}

void ACStaticArmor::MoveTo(FName InSocket)
{
	/*if (OnSocket == false)
	{
		AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocket);
		OnSocket = true;
	}
	else
	{
		AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), SocketName);
		OnSocket = false;

	}*/

	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocket);

}

