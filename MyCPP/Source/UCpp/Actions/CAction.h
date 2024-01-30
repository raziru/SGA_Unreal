// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Actions/CAttachment.h"
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
class UCPP_API UCAction : public UObject
{
	GENERATED_BODY()
public:
    friend class UCActionData;
public:
    FORCEINLINE class ACEquipment* GetEquipment() { return Equipment; }
    FORCEINLINE class ACDoAction* GetDoAction() { return DoAction; }
    FORCEINLINE class ACAttachment** GetAttachments() { return Attachments; }
    FORCEINLINE FLinearColor GetEquipmentColor() { return EquipmentColor; }

    FORCEINLINE class ACAttachment* GetMainAttachment() { return Attachments[(int32)EAttachment::MainHand]; }
    FORCEINLINE class ACAttachment* GetSecondAttachment() { return Attachments[(int32)EAttachment::SecondHand]; }
    FORCEINLINE class ACAttachment* GetProjectileAttachment() { return Attachments[(int32)EAttachment::Projectile]; }



    void AttachmentOnCollision();
    void AttachmentOffCollision();

    bool GetAttachment();
public:
     void DestroyActor();

private:
    class ACEquipment* Equipment;
    class ACAttachment* Attachments[(int32)EAttachment::Max];
    class ACDoAction* DoAction;


    FLinearColor EquipmentColor;

};
