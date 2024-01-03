// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CThrow_Magic.generated.h"

UCLASS()
class UCPP_API ACThrow_Magic : public ACThrow
{
	GENERATED_BODY()

public:
	ACThrow_Magic();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* Sphere;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Particle;
};
