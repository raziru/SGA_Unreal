// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C04_Override.generated.h"

UCLASS()
class UCPP_API AC04_Override : public AActor
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
	AC04_Override();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintImplementableEvent)//몸체없이 블프에서 정의가능, 순수 가상함수처럼 작동
		void ChangeColorRed();

	UFUNCTION(BlueprintNativeEvent)
		void ChangeColorWhite();
	void ChangeColorWhite_Implementation();//가상함수의 기본 정의를 하는 과정 
	//재정의시 c에서 정의한 것은 무시된다.

private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
