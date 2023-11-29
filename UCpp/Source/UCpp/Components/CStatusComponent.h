// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"


UCLASS( ClassGroup=(GameProject), meta=(BlueprintSpawnableComponent) )
class UCPP_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()
private:
    UPROPERTY(EditDefaultsOnly, Category = "Health")//������ ǥ���Ǵ� ����
        float MaxHealth = 100;

    UPROPERTY(EditDefaultsOnly, Category = "Speed")
        float WalkSpeed = 200.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Speed")
        float RunkSpeed = 400.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Speed")
        float SprintSpeed = 600.0f;

public:
    FORCEINLINE float GetMaxHealth() { return MaxHealth; }
    FORCEINLINE float GetHealth() { return Health; }

    FORCEINLINE float GetWalkSpeed() { return WalkSpeed; }
    FORCEINLINE float GetRunkSpeed() { return RunkSpeed; }
    FORCEINLINE float GetSprintSpeed() { return SprintSpeed; }

    FORCEINLINE bool CanMove() { return bCanMove; }
public:	
	UCStatusComponent();

    void AddHealth(float InAmount);
    void SubHealth(float InAmount);

    void SetMove();
    void SetStop();
protected:
	virtual void BeginPlay() override;


private:
    float Health;

    bool bCanMove = true;
};
