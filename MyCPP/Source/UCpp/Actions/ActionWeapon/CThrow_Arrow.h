// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionWeapon/CThrow.h"
#include "CThrow_Arrow.generated.h"

UCLASS()
class UCPP_API ACThrow_Arrow : public ACThrow
{
	GENERATED_BODY()
public:
	ACThrow_Arrow();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* Sphere;

	/*UPROPERTY(VisibleDefaultsOnly)
		class UStaticmeshComponent* Mesh;*/

};
