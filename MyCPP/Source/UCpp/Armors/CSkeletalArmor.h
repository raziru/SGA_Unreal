// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Armors/CArmor.h"
#include "CSkeletalArmor.generated.h"

/**
 * 
 */
UCLASS()
class UCPP_API ACSkeletalArmor : public ACArmor
{
	GENERATED_BODY()
public:
	ACSkeletalArmor();
public:
	UPROPERTY(EditDefaultsOnly, Category = "Armor")
		class USkeletalMeshComponent* Mesh;
protected:
	virtual void Attachment(class ACharacter* OwnerCharacter, FName InSocketName) override;
	virtual void Detachment() override;
};
