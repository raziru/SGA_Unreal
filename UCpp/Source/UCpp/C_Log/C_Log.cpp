// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Log/C_Log.h"
#include "Global.h"
// Sets default values
AC_Log::AC_Log()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_Log::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_Log::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

