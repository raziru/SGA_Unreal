// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C05_MultiCastTrigger.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiLightBeginOverlap, int32, FLinearColor);

UCLASS()
class U02_CPP_API AC05_MultiCastTrigger : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
public:	
	// Sets default values for this actor's properties
	AC05_MultiCastTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
public:
	FMultiLightBeginOverlap OnMultiLightBeginOverlap;
};
