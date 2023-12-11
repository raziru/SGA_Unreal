// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"//Using Vector cross, dot product
#include "CTargetComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPP_API UCTargetComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
		float TraceRadius = 1000.0f;

	UPROPERTY(EditAnywhere)
		float InteropSpeed = 2.5f;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<EDrawDebugTrace::Type> Debug;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* Particle;

public:	
	// Sets default values for this component's properties
	UCTargetComponent();
protected:
	virtual void BeginPlay() override;

public:
	void ToggleTarget();
	void ChangeTargetLeft();
	void ChangeTargetRight();

private:
	void StartTargeting();
	void EndTargeting();

	void SetTraceTargets();
	void SetTarget();

	void ChangeTarget(bool InRight);
	void ChangeCursor(class ACharacter* InTarget);



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	class ACharacter* OwnerCharacter;
	class ACharacter* Target;
	class UParticleSystemComponent* Attached;

	TArray<class ACharacter*> TraceTargets;
};
