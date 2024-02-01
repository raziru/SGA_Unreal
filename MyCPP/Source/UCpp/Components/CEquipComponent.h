// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Armors/CArmor.h"
#include "CEquipComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetNewStatus, FStatusData, NewStatus);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShield, class ACAttachment* , Shield);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOffShield, class ACAttachment*, Shield);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHandShield);

UCLASS( ClassGroup=(GameProject), meta=(BlueprintSpawnableComponent) )
class UCPP_API UCEquipComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCEquipComponent();

public:
	UFUNCTION()
		void SetNewArmor(TSubclassOf<class ACArmor> NewArmorClass);

	void SetStatus();

	void OnSecondEquip(EArmorType InArmorType);

	void OnSecondUnEquip(EArmorType InArmorType);


private:
	ACharacter* OwnerCharacter;

private:
	FStatusData EquipStatus;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Armors")
		TMap<EArmorType, ACArmor*> Armors;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
		FSetNewStatus SetNewStatus;

	UPROPERTY(BlueprintAssignable)
		FOnShield OnShield;

	UPROPERTY(BlueprintAssignable)
		FOffShield OffShield;

	UPROPERTY(BlueprintAssignable)
		FOnHandShield OnHandShield;
};
