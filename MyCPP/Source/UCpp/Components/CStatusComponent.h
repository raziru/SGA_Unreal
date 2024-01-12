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
    UPROPERTY(EditDefaultsOnly, Category = "Health")//������ ǥ���Ǵ� ����
        float MaxHealth;

    UPROPERTY(EditDefaultsOnly, Category = "Mana")//������ ǥ���Ǵ� ����
        float MaxMana;

    UPROPERTY(EditDefaultsOnly, Category = "Speed")
        float WalkSpeed;

    UPROPERTY(EditDefaultsOnly, Category = "Speed")
        float RunSpeed;

    UPROPERTY(EditDefaultsOnly, Category = "Speed")
        float SprintSpeed;

    //Operator overloading for add operation
    void operator +=(const FStatusData& other)
    {
        this->MaxHealth     += other.MaxHealth;

        this->MaxMana     += other.MaxMana;
        
        this->WalkSpeed   += other.WalkSpeed;
        this->RunSpeed    += other.RunSpeed;
        this->SprintSpeed += other.SprintSpeed;
    }

    FStatusData operator +(const FStatusData& other)
    {
        FStatusData result;
        result.MaxHealth   = this->MaxHealth   + other.MaxHealth;

        result.MaxMana     = this->MaxMana     + other.MaxMana  ;


        result.WalkSpeed   = this->WalkSpeed   + other.WalkSpeed;
        result.RunSpeed    = this->RunSpeed    + other.RunSpeed;
        result.SprintSpeed = this->SprintSpeed + other.SprintSpeed;
        return result;
    }
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRefreshStatus, FStatusData, NewStatus);

UCLASS( ClassGroup=(GameProject), meta=(BlueprintSpawnableComponent) )
class UCPP_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()
private:
    //UPROPERTY(EditDefaultsOnly, Category = "Health")//������ ǥ���Ǵ� ����
    //    float MaxHealth = 100;

    //UPROPERTY(EditDefaultsOnly, Category = "Speed")
    //    float WalkSpeed = 600.0f;

    //UPROPERTY(EditDefaultsOnly, Category = "Speed")
    //    float RunSpeed = 800.0f;

    //UPROPERTY(EditDefaultsOnly, Category = "Speed")
    //    float SprintSpeed = 600.0f;
    UPROPERTY(EditDefaultsOnly, Category = "DefaultStatus")
        FStatusData DefaultStatus;
    //UPROPERTY(EditDefaultsOnly, Category = "DefaultStatus")
    FStatusData CurrentStatus;

public:
    FORCEINLINE float GetMaxHealth()   { return CurrentStatus.MaxHealth; }
    FORCEINLINE float GetHealth()      { return Health; }

    FORCEINLINE float GetMaxMana() { return CurrentStatus.MaxMana; }
    FORCEINLINE float GetMana() { return Mana; }

    FORCEINLINE FStatusData GetStatusData() { return CurrentStatus; }

    FORCEINLINE float GetWalkSpeed()   { return CurrentStatus.WalkSpeed; }
    FORCEINLINE float GetRunSpeed()    { return CurrentStatus.RunSpeed; }
    FORCEINLINE float GetSprintSpeed() { return CurrentStatus.SprintSpeed; }

    FORCEINLINE bool CanMove() { return bCanMove; }
public:	
	UCStatusComponent();

    void AddHealth(float InAmount);
    void SubHealth(float InAmount);

    void AddMana(float InAmount);
    void SubMana(float InAmount);

    void SetMove();
    void SetStop();



    void SetNewStatus(const FStatusData NewStatus);


protected:
	virtual void BeginPlay() override;

public:
    UPROPERTY(BlueprintAssignable)
        FRefreshStatus RefreshStatus;

private:
    float Health;
    float Mana;

    bool bCanMove = true;
};
