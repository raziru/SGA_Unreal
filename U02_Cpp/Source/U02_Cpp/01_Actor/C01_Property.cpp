// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Actor/C01_Property.h"

int AC01_Property::Hello()
{
	return 300;
}

// Sets default values
AC01_Property::AC01_Property()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC01_Property::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC01_Property::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

