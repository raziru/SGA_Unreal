// Fill out your copyright notice in the Description page of Project Settings.


#include "C01_Property.h"

AC01_Property::AC01_Property()
{
	PrimaryActorTick.bCanEverTick = true;
	C = 50;
}

void AC01_Property::BeginPlay()
{
	Super::BeginPlay();
	//FString str;
	/*str.Append("A : ");
	str.Append(FString::FromInt(A));
	str.Append(", B : ");
	str.Append(FString::FromInt(B));
	str.Append(", C : ");
	str.Append(FString::FromInt(C));

	GLog->Log(str);*/
}

void AC01_Property::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

