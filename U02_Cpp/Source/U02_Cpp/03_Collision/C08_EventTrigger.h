// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C08_EventTrigger.generated.h"

UCLASS()
class U02_CPP_API AC08_EventTrigger : public AActor
{
	GENERATED_BODY()
public:
	DECLARE_EVENT_OneParam(AC08_EventTrigger, FEventTigger, int32)
	//무조건 클래스 내부에서 생성해야함, 클래스 이름도 가져야함, event는 return 타입이없음

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
public:	
	AC08_EventTrigger();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	FEventTigger OnEventTrigger;

};
