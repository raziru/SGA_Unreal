// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Collision/C_ActorBeginOverlap.h"

// Sets default values
AC_ActorBeginOverlap::AC_ActorBeginOverlap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_ActorBeginOverlap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_ActorBeginOverlap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

