// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Debug/C01_Log.h"
#include "Global.h"

AC01_Log::AC01_Log()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AC01_Log::BeginPlay()
{
	Super::BeginPlay();
	CLog::Print(10);

	CLog::Print(20, 1);
	CLog::Print(30, 2, 20.0f);
	CLog::Print(40, 2, 20.0f);

	CLog::Print("Unreal GamePlay!");
	CLog::Print(GetActorLocation());
	CLog::Print(GetActorRotation());

	CLog::Log(10);
	CLog::Log(PI);
	CLog::Log("Unreal Gameplay!");
	CLog::Log(GetActorLocation());
	CLog::Log(GetActorRotation());

	CLog::Log(this);
	//CLog::Log(__FUNCTION__, __LINE__);

	PrintLine();
}

void AC01_Log::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Time += DeltaTime;
	CLog::Print(Time, 3);
}

