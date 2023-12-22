// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Armors/CArmor.h"
#include "CEquipComponent.generated.h"


UCLASS( ClassGroup=(GameProject), meta=(BlueprintSpawnableComponent) )
class UCPP_API UCEquipComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCEquipComponent();

public:
	void SetNewArmor(TSubclassOf<class ACArmor> NewArmorClass);

private:
	ACharacter* OwnerCharacter;
private:
	FStatusData EquipStatus;

private:
	/*UPROPERTY(EditDefaultsOnly, Category = "Armors")
		class TSubclassOf<class ACArmor> ArmorClass[(int32)EArmorType::Max];

	UPROPERTY(EditDefaultsOnly, Category = "Armors")
		FName SocketNames[(int32)EArmorType::Max];*/

	UPROPERTY(EditDefaultsOnly, Category = "Armors")
		TMap<EArmorType, ACArmor*> Armors;
protected:
	virtual void BeginPlay() override;

		
};
