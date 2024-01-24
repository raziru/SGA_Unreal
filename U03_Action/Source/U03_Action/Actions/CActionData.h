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
    //�����͸� ä��� ���� ��ȹ�� ���̱� ������ �����ڴ� �������� �����༭ �������Ʈ���� ���۰����ϰ� �ؾ��Ѵ�.
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
