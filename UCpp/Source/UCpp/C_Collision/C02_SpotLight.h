// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_SpotLight.generated.h"

UCLASS()
class UCPP_API AC02_SpotLight : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

	UPROPERTY(VisibleDefaultsOnly)
		class USpotLightComponent* SpotLights[3];
public:	
	AC02_SpotLight();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnLightColor(int32 InIndex, FLinearColor InColor);

};
