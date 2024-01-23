// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"


UENUM(BlueprintType)
enum class ECharacterSpeed : uint8
{
    Walk, Run, Sprint, Max,
};

UCLASS( ClassGroup=(GameProject), meta=(BlueprintSpawnableComponent) )
class U03_ACTION_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()

private:
    UPROPERTY(EditDefaultsOnly, Category = "Health")
        float MaxHealth = 100;

    UPROPERTY(EditDefaultsOnly, Category = "Speed")
        float Speed[(int32)ECharacterSpeed::Max] = { 200, 400, 600 };

public:
    FORCEINLINE float GetMaxHealth() { return MaxHealth; }
    FORCEINLINE float GetHealth() { return Health; }

    FORCEINLINE float GetWalkSpeed()   { return Speed[(int32)ECharacterSpeed::Walk]; }
    FORCEINLINE float GetRunkSpeed()   { return Speed[(int32)ECharacterSpeed::Run]; }
    FORCEINLINE float GetSprintSpeed() { return Speed[(int32)ECharacterSpeed::Sprint]; }

    FORCEINLINE bool CanMove() { return bCanMove; }

public:
    UCStatusComponent();

    void AddHealth(float InAmount);
    void SubHealth(float InAmount);

    void SetMove();
    void SetStop();

    void SetSpeed(ECharacterSpeed InType);
protected:
    virtual void BeginPlay() override;

private:
    float Health;

    bool bCanMove = true;

};
