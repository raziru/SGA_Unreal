// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CEquipComponent.generated.h"

UENUM(BlueprintType)
enum class EArmorType : uint8
{
	Weapon, Helmet, Top, Bottom, Shoes, Hands, Shield, Max,
};

UCLASS( ClassGroup=(GameProject), meta=(BlueprintSpawnableComponent) )
class UCPP_API UCEquipComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCEquipComponent();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Armors")
		class TSubclassOf<class ACArmor> Armors[(int32)EArmorType::Max];




protected:
	virtual void BeginPlay() override;

		
};
