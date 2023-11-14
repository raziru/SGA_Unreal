// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Actor/C_Actor.h"
#include "Global.h"
// Sets default values
AC_Actor::AC_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>
		("Mesh");
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AC_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}


