// Fill out your copyright notice in the Description page of Project Settings.


#include "CSkeletalArmor.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/SkinnedMeshComponent.h"

ACSkeletalArmor::ACSkeletalArmor()
{
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh");

}
void ACSkeletalArmor::Attach()
{
	FName Empty = "";
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), Empty);
	Mesh->SetMasterPoseComponent(OwnerCharacter->GetMesh());
	if (OnAttach.IsBound())
	{
		OnAttach.Broadcast(StatusData);
	}
}

void ACSkeletalArmor::Detach()
{

	Mesh->UnbindClothFromMasterPoseComponent();
	DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepRelative, true));
	if (OnDetach.IsBound())
	{
		OnDetach.Broadcast(StatusData);
	}
	Destroy();
}
