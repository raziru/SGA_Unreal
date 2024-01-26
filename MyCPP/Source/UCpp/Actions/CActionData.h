// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CAction.h"
#include "CActionData.generated.h"



UCLASS()
class UCPP_API UCActionData : public UDataAsset
{
	GENERATED_BODY()

// For Blueprint// 블루 프린트로 내용 수정을 마음대로 할 수 있기 하기위함
public:
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        TSubclassOf<class ACAttachment> AttachmentClass;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        TSubclassOf<class ACAttachment> SecondAttachmentClass;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        TSubclassOf<class ACEquipment> EquipmentClass;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        FEquipmentData EquipmentData;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        FLinearColor EquipmentColor;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        TSubclassOf<class ACDoAction> DoActionClass;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        TArray<FDoActionData> DoActionDatas;//TArray: vector, Unreal이 제공하는 컨테이너이다.

public:
    void BeginPlay(class ACharacter* InOwnerCharacter, class UCAction** OutAction);
    void DataDestroy();

private:
    FString GetLabelName(class ACharacter* InOwnerCharacter, FString InName);

};
