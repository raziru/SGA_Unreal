// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CActionData.generated.h"

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


};

UCLASS()
class U03_ACTION_API UCActionData : public UDataAsset
{
	GENERATED_BODY()
	
public:
    FORCEINLINE class ACEquipment* GetEquipment() { return Equipment; }
    FORCEINLINE class ACDoAction* GetDoAction() { return DoAction; }
    FORCEINLINE class ACAttachment* GetAttachment() { return Attachment; }


public:
    //데이터를 채우는 것은 기획의 일이기 때문에 개발자는 변수들을 열어줘서 블루프린트에서 조작가능하게 해야한다.
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        TSubclassOf<class ACAttachment> AttachmentClass;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        TSubclassOf<class ACEquipment> EquipmentClass;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        FEquipmentData EquipmentData;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        FLinearColor EquipmentColor;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        TSubclassOf<class ACDoAction> DoActionClass;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        TArray<FDoActionData> DoActionDatas;

public:
    void BeginPlay(class ACharacter* InOwnerCharacter);

private:
    class ACEquipment* Equipment;
    class ACAttachment* Attachment;
    class ACDoAction* DoAction;
};
