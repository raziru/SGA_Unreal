// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"



USTRUCT(BlueprintType)
struct FStatusData
{
    GENERATED_BODY()
public:
    UPROPERTY(EditDefaultsOnly, Category = "Health")//블프에 표현되는 스탯
        float MaxHealth;

    UPROPERTY(EditDefaultsOnly, Category = "Speed")
        float WalkSpeed;

    UPROPERTY(EditDefaultsOnly, Category = "Speed")
        float RunSpeed;

    UPROPERTY(EditDefaultsOnly, Category = "Speed")
        float SprintSpeed;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRefreshStatus);

UCLASS( ClassGroup=(GameProject), meta=(BlueprintSpawnableComponent) )
class UCPP_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()
private:
    UPROPERTY(EditDefaultsOnly, Category = "Health")//블프에 표현되는 스탯
        float MaxHealth = 100;

    UPROPERTY(EditDefaultsOnly, Category = "Speed")
        float WalkSpeed = 600.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Speed")
        float RunSpeed = 800.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Speed")
        float SprintSpeed = 600.0f;

public:
    FORCEINLINE float GetMaxHealth() { return MaxHealth; }
    FORCEINLINE float GetHealth() { return Health; }

    FORCEINLINE float GetWalkSpeed() { return WalkSpeed; }
    FORCEINLINE float GetRunSpeed() { return RunSpeed; }
    FORCEINLINE float GetSprintSpeed() { return SprintSpeed; }

    FORCEINLINE bool CanMove() { return bCanMove; }
public:	
	UCStatusComponent();

    void AddHealth(float InAmount);
    void SubHealth(float InAmount);

    void SetMove();
    void SetStop();

    void AddStatus(const FStatusData NewStatus);
    void SubStatus(const FStatusData NewStatus);

protected:
	virtual void BeginPlay() override;

public:
    UPROPERTY(BlueprintAssignable)
        FRefreshStatus RefreshStatus;

private:
    float Health;

    bool bCanMove = true;
};
