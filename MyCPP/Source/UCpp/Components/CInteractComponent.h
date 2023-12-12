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
	UPROPERTY(EditDefaultsOnly, Category = "Interact")
		class ACInteract* InteractSystem;
public:	
	UCInteractComponent();

	void Interact();

	UFUNCTION()
		void OnInteractBeginOverlap(class AActor* InInteracted);

	UFUNCTION()
		void OnInteractEndOverlap  (class AActor* InInteracted);

protected:
	virtual void BeginPlay() override;



private:
	TArray<class IIInteract*> InteractArray;

};
