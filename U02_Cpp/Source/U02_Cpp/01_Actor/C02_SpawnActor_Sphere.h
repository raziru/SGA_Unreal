// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Actor/C02_SpawnActor.h"

#include "C02_SpawnActor_Sphere.generated.h"

UCLASS()
class U02_CPP_API AC02_SpawnActor_Sphere : public AC02_SpawnActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AC02_SpawnActor_Sphere();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame

};
