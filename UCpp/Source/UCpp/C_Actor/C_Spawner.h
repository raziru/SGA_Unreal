// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Spawner.generated.h"

UCLASS()
class UCPP_API AC_Spawner : public AActor
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AC_Actor> SpawnClass[3];
public:	
	// Sets default values for this actor's properties
	AC_Spawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	class AC_Actor* SpawnActors[3];

};
