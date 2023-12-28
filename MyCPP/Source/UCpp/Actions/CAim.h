// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/TimelineComponent.h"
#include "CAim.generated.h"

/**
 * 
 */
UCLASS()
class UCPP_API UCAim : public UObject
{
	GENERATED_BODY()
public:
	FORCEINLINE bool IsAvaliable() { return SpringArm != NULL && Camera != NULL; }
	FORCEINLINE bool IsZoom() { return bInZoom; }

public:
	UCAim();
	void BeginPlay(class ACharacter* InCharacter);

	void OnZoom();
	void OffZoom();

	void Tick(float DeltaTime);

private:
	UFUNCTION()
		void Zooming(float Output);

private:
	class UCurveFloat* Curve;

	class ACHUD* HUD;

	class ACharacter* OwnerCharacter;
	class UCStateComponent* State;
	class USpringArmComponent* SpringArm;
	class UCameraComponent* Camera;

	bool bInZoom;

	FTimeline Timeline;
	FOnTimelineFloat TimelineFloat;
};
