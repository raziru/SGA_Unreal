// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C01_Property.generated.h"

UCLASS()
class U02_CPP_API AC01_Property : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		int A = 10;

	UPROPERTY(EditInstanceOnly)
		int B = 10;

	UPROPERTY(EditDefaultsOnly)
		int C;


protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int Test = 20;

	UFUNCTION(BlueprintPure)
		int Hello();


public:	


	AC01_Property();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
