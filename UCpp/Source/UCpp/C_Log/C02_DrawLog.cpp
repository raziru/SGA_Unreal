// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Log/C02_DrawLog.h"
#include "Global.h"

// Sets default values
AC02_DrawLog::AC02_DrawLog()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitLocation[0] = FVector::ZeroVector;
	InitLocation[1] = FVector(0, 1000, 0);
	InitLocation[2] = FVector(0, 400, 0);
	InitLocation[3] = FVector(0, 1600, 0);
	InitLocation[4] = FVector(300, 1000, 0);

	Box = FBox(FVector(-50, -100, -50), FVector(50, 100, 50));
	Transform.SetLocation(FVector(200, 1600, 0));
}

// Called when the game starts or when spawned
void AC02_DrawLog::BeginPlay()
{
	Super::BeginPlay();
	for (int32 i = 0; i < 5; i++)
		Location[i] = InitLocation[i] + GetActorLocation();

	//DrawDebugBox(GetWorld(), Location[0] + Box.GetCenter(), Box.GetExtent(), FColor::Red, true);
}

// Called every frame
void AC02_DrawLog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (int32 i = 0; i < 5; i++)
		Location[i] = InitLocation[i] + GetActorLocation();


	DrawDebugSolidBox(GetWorld(), Location[0] + Box.GetCenter(), Box.GetExtent(), FColor::Red);

	DrawDebugPoint(GetWorld(), Location[1], 100, FColor::Red);
	DrawDebugSphere(GetWorld(), Location[2], 100, 50, FColor::Green);
	DrawDebugCircle(GetWorld(), Location[3], 100, 60, FColor::Blue);

	DrawDebugLine(GetWorld(), Location[2], Location[3], FColor::Magenta, false, -1, 0, 2);


	FVector location = Location[1];
	location.X += 100;
	location.Z += 100;
	location.Y += sin(GetWorld()->GetTimeSeconds() * 3.0f) * 300.0f;

	DrawDebugPoint(GetWorld(), location, 100, FColor::Emerald);

	DrawDebugDirectionalArrow(GetWorld(), location, Location[3], 360, FColor::Yellow, false, -1, 0, 10);
}

