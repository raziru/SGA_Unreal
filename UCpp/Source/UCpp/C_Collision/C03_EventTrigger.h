// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C03_EventTrigger.generated.h"

UCLASS()
class UCPP_API AC03_EventTrigger : public AActor
{
	GENERATED_BODY()
public:
	DECLARE_EVENT_OneParam(AC03_EventTrigger, FEventTigger, int32)
	//������ Ŭ���� ���ο��� �����ؾ���, Ŭ���� �̸��� ��������, event�� return Ÿ���̾���

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
public:	
	// Sets default values for this actor's properties
	AC03_EventTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	FEventTigger OnEventTrigger;

};
