// Fill out your copyright notice in the Description page of Project Settings.


#include "CSkeletalArmor.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/SkinnedMeshComponent.h"

ACSkeletalArmor::ACSkeletalArmor()
{
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh");

}
void ACSkeletalArmor::Attachment()
{
	FName Empty = "";
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), Empty);
	Mesh->SetMasterPoseComponent(OwnerCharacter->GetMesh());

	if (OnAttachmentDelegate.IsBound())
	{
		OnAttachmentDelegate.Broadcast(StatusData);
	}
}

void ACSkeletalArmor::Detachment()
{

	Mesh->UnbindClothFromMasterPoseComponent();
	DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepRelative, true));
	if (OnDetachmentDelegate.IsBound())
	{
		OnDetachmentDelegate.Broadcast(StatusData);
	}
	Destroy();
}
