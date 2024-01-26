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

// For Blueprint// ��� ����Ʈ�� ���� ������ ������� �� �� �ֱ� �ϱ�����
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
        TArray<FDoActionData> DoActionDatas;//TArray: vector, Unreal�� �����ϴ� �����̳��̴�.

public:
    void BeginPlay(class ACharacter* InOwnerCharacter, class UCAction** OutAction);
    void DataDestroy();

private:
    FString GetLabelName(class ACharacter* InOwnerCharacter, FString InName);

};
