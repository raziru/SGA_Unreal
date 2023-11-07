// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C03_Spawner.generated.h"

UCLASS()
class U02_CPP_API AC03_Spawner : public AActor
{
	GENERATED_BODY()


private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AC02_SpawnActor> SpawnClass[3];
public:	
	AC03_Spawner();

protected:
	virtual void BeginPlay() override;

private:
	class AC02_SpawnActor* SpawnActors[3];

};
