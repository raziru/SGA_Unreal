// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Warp.generated.h"


UCLASS()
class UCPP_API ACDoAction_Warp : public ACDoAction
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	virtual void DoAction()       override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction()   override;

	virtual void DoSecondAction() override;
	virtual void DoSecondActionRelease() override;


	virtual void OnAim() override;
	virtual void OffAim() override;

	virtual void Tick(float DeltaTime) override;

private:
	bool GetCrursorLocationAndRotation(FVector& OutLocation, FRotator& OutRotator);

private:
	class UDecalComponent* Decal;
	FVector Location;

	class UCAim* Aim;
};
