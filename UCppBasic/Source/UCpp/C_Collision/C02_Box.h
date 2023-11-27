// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_Box.generated.h"

UCLASS()
class UCPP_API AC02_Box : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh[3];
public:	
	AC02_Box();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnPhysics(int32 InIndex, FLinearColor InColor);

private:
	UMaterialInstanceDynamic* Materials[3];

	FVector WorldLocation[3];

};
