// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Components/CActionComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CFeetComponent.h"
#include "CAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UCPP_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        float Speed;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        float Direction;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        EActionType ActionType;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        bool PressAction;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        bool PressSecondAction;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        bool OnShield;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        bool SecondHand;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        FFeetData FeetData;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        float Pitch;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        bool IsDead;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        bool IsFalling;
public:
    virtual void NativeBeginPlay() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
    UFUNCTION()
        void OnActionTypeChanged(EActionType InPrevType, EActionType InNewType);

    UFUNCTION()
        void OnActionPress(bool InPressAction, bool InPressSecondAction);

    UFUNCTION()
        void OnSecondHand(bool InSecondHand);
};
