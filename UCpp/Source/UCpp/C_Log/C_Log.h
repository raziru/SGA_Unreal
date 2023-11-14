// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Log.generated.h"

UCLASS()
class UCPP_API AC_Log : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_Log();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
