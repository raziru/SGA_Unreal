// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Armors/CArmor.h"
#include "CStaticArmor.generated.h"

/**
 * 
 */
UCLASS()
class UCPP_API ACStaticArmor : public ACArmor
{
	GENERATED_BODY()
public:
	ACStaticArmor();
public:
	UPROPERTY(EditDefaultsOnly, Category = "Armor")
		class UStaticMeshComponent* Mesh;


	virtual void AttachTo(FName InSocket) override;

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FName SocketName;

protected:
	virtual void Attachment() override;
	virtual void Detachment() override;

private:
	bool OnSocket;
};
