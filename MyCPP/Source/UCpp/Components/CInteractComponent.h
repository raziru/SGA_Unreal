// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CInteractComponent.generated.h"


UCLASS( ClassGroup=(GameProject), meta=(BlueprintSpawnableComponent) )
class UCPP_API UCInteractComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class UCUserWidget_Interact* InteractWidget;
	UPROPERTY()
		TSubclassOf<UCUserWidget_Interact> InteractClass;

public:	
	UCInteractComponent();

	void Interact();



private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void UpdateWidget();
protected:
	virtual void BeginPlay() override;




private:
	TArray<class IIInteract*> InteractArray;

	TArray<class UShapeComponent*> InteractBox;
	
};
