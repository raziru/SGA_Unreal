// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState_Equip.generated.h"

UCLASS()
class U02_CPP_API UCAnimNotifyState_Equip : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	FString GetNotifyName_Implementation() const;//blueprint���� ǥ�� ������

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};
