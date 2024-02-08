// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotify_EndBackstep.h"
#include "Global.h"
#include "Characters/ICharacter.h"
#include "Characters/CPlayer.h"

FString UCAnimNotify_EndBackstep::GetNotifyName_Implementation() const
{
	return "Backstep";
}

void UCAnimNotify_EndBackstep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	IICharacter* character = Cast<IICharacter>(MeshComp->GetOwner());
	CheckNull(character);

	character->End_Backstep();
}