// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_EndBackstep.generated.h"

UCLASS()
class U03_ACTION_API UCAnimNotify_EndBackstep : public UAnimNotify
{

	GENERATED_BODY()
		
public:

	FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
