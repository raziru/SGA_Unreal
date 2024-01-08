// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"	
#include "Actions/CActionData.h"
#include "CEquipment.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnequipmentDelegate);
UCLASS()
class UCPP_API ACEquipment : public AActor
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetData(FEquipmentData InData) { Data = InData; }
	FORCEINLINE void SetColor(FLinearColor InColor) { Color = InColor; }
	FORCEINLINE const bool* GetEquipped() { return &bEquipped; }
public:	
	// Sets default values for this actor's properties
	ACEquipment();
public:
	//���� ���
	UFUNCTION(BlueprintNativeEvent)
		void Equip();
	void Equip_Implementation();

	//���� ����
	UFUNCTION(BlueprintNativeEvent)
		void Begin_Equip();
	void Begin_Equip_Implementation();

	//���� �Ϸ�
	UFUNCTION(BlueprintNativeEvent)
		void End_Equip();
	void End_Equip_Implementation();


	//���� ���
	UFUNCTION(BlueprintNativeEvent)
		void Unequip();
	void Unequip_Implementation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//virtual void Destory() override;
public:
	UPROPERTY(BlueprintAssignable)
		FEquipmentDelegate OnEquipmentDelegate;

	UPROPERTY(BlueprintAssignable)
		FUnequipmentDelegate OnUnequipmentDelegate;


protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;

	UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* Status;

private:
	bool bEquipped;
	FEquipmentData Data;
	FLinearColor Color;

};
