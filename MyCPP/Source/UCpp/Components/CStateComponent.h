// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"


UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle, Roll, Backstep, Equip, Action, Hitted, Dead, Jump, Max,
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChanged, EStateType, InPrevType, EStateType, InNewType);
UCLASS( ClassGroup=(GameProject), meta=(BlueprintSpawnableComponent) )
class UCPP_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsIdleMode() { return Type == EStateType::Idle; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsRollMode() { return Type == EStateType::Roll; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsBackstepMode() { return Type == EStateType::Backstep; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsEquipMode() { return Type == EStateType::Equip; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsActionMode() { return Type == EStateType::Action; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsHittedMode() { return Type == EStateType::Hitted; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsDeadMode() { return Type == EStateType::Dead; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsJumpMode() { return Type == EStateType::Jump; }

public:	
	// Sets default values for this component's properties
	UCStateComponent();

public:
	void SetIdleMode();
	void SetRollMode();
	void SetBackstepMode();
	void SetEquipMode();
	void SetActionMode();
	void SetHittedMode();
	void SetDeadMode();
	void SetJumpMode();


private:
	void ChangeType(EStateType InType);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:
	UPROPERTY(BlueprintAssignable)
		FStateTypeChanged OnStateTypeChanged;

private:
	EStateType Type;

		
};
