// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAction.generated.h"

USTRUCT(BlueprintType)
struct FEquipmentData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
        class UAnimMontage* AnimMontage;

    UPROPERTY(EditAnywhere)
        float PlayRatio = 1.0f;

    UPROPERTY(EditAnywhere)
        FName StartSection;

    UPROPERTY(EditAnywhere)
        bool bCanMove = true;

    UPROPERTY(EditAnywhere)
        bool bPawnControl = true;
};

USTRUCT(BlueprintType)
struct FDoActionData : public FEquipmentData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
        float Power = 5.0f;

    UPROPERTY(EditAnywhere)
        float HitStop;

    UPROPERTY(EditAnywhere)
        class UParticleSystem* Effect;

    UPROPERTY(EditAnywhere)
        FTransform EffectTransform;

    UPROPERTY(EditAnywhere)
        TSubclassOf<class UCameraShakeBase> ShakeClass;

    UPROPERTY(EditAnywhere)
        TSubclassOf<class ACThrow> ThrowClass;
};
UCLASS()
class U03_ACTION_API UCAction : public UObject
{
	GENERATED_BODY()
public:
    friend class UCActionData;

public:
    FORCEINLINE class ACEquipment* GetEquipment() { return Equipment; }
    FORCEINLINE class ACDoAction* GetDoAction() { return DoAction; }
    FORCEINLINE class ACAttachment* GetAttachment() { return Attachment; }

    FORCEINLINE FLinearColor GetEquipmentColor() { return EquipmentColor; }
private:
    class ACEquipment* Equipment;
    class ACAttachment* Attachment;
    class ACDoAction* DoAction;

    FLinearColor EquipmentColor;
};