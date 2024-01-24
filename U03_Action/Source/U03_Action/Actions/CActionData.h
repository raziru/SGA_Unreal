// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CActionData.generated.h"



UCLASS()
class U03_ACTION_API UCActionData : public UDataAsset
{
	GENERATED_BODY()


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
    void BeginPlay(class ACharacter* InOwnerCharacter, class UCAction** OutAction);

private:
    FString GetLableName(class ACharacter* InOwnerCharacter, FString InName);


};
