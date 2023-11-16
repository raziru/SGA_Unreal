// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C03_Cube.generated.h"

UCLASS()
class U02_CPP_API AC03_Cube : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;
public:	
	AC03_Cube();

protected:
	virtual void BeginPlay() override;


};
