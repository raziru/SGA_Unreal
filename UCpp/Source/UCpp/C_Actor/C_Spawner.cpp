// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Actor/C_Spawner.h"
#include "Global.h"
#include "C_Actor.h"

// Sets default values
AC_Spawner::AC_Spawner()
{

}

// Called when the game starts or when spawned
void AC_Spawner::BeginPlay()
{
	Super::BeginPlay();
	for (int32 i = 0; i < 3; i++)
	{
		FVector location = GetActorLocation();

		FTransform transform;
		//transform.SetLocation(FVector(location.X + i * 400,location.Y,location.Z));

		SpawnActors[i] = GetWorld()->SpawnActor<AC_Actor>(SpawnClass[i], transform);


		SpawnActors[i]->SetActorLocation(FVector(FVector(location.X + i * 400, location.Y, location.Z)));
	}
}



