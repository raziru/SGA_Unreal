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
USTRUCT(BlueprintType)
struct FStatusData
{
    GENERATED_BODY()
public:
    UPROPERTY(EditDefaultsOnly, Category = "Health")//블프에 표현되는 스탯
        float MaxHealth;

    UPROPERTY(EditDefaultsOnly, Category = "Mana")//블프에 표현되는 스탯
        float MaxMana;

    UPROPERTY(EditDefaultsOnly, Category = "Speed")
        float Speed[(int32)ECharacterSpeed::Max] = { 200, 400, 600 };

    UPROPERTY(EditDefaultsOnly, Category = "Speed")
        ECharacterSpeed CurrentSpeed = ECharacterSpeed::Run;

    //Operator overloading for add operation
    void operator +=(const FStatusData& other)
    {
        this->MaxHealth     += other.MaxHealth;
        this->MaxMana     += other.MaxMana;
        
        this->Speed[(int32)ECharacterSpeed::Walk]   += other.Speed[(int32)ECharacterSpeed::Walk];
        this->Speed[(int32)ECharacterSpeed::Run]    += other.Speed[(int32)ECharacterSpeed::Run];
        this->Speed[(int32)ECharacterSpeed::Sprint] += other.Speed[(int32)ECharacterSpeed::Sprint];

    }

    FStatusData operator +(const FStatusData& other)
    {
        FStatusData result;

        result.MaxHealth   = this->MaxHealth   + other.MaxHealth;
        result.MaxMana     = this->MaxMana     + other.MaxMana  ;

        result.Speed[(int32)ECharacterSpeed::Walk]   = this->Speed[(int32)ECharacterSpeed::Walk] + other.Speed[(int32)ECharacterSpeed::Walk];
        result.Speed[(int32)ECharacterSpeed::Run]    = this->Speed[(int32)ECharacterSpeed::Run] + other.Speed[(int32)ECharacterSpeed::Run];
        result.Speed[(int32)ECharacterSpeed::Sprint] = this->Speed[(int32)ECharacterSpeed::Sprint] + other.Speed[(int32)ECharacterSpeed::Sprint];

        return result;
    }
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRefreshStatus, FStatusData, NewStatus);

UCLASS( ClassGroup=(GameProject), meta=(BlueprintSpawnableComponent) )
class UCPP_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()
private:
    
    UPROPERTY(EditDefaultsOnly, Category = "DefaultStatus")
        FStatusData DefaultStatus;

    FStatusData CurrentStatus;

public:
    FORCEINLINE float GetMaxHealth()   { return CurrentStatus.MaxHealth; }
    FORCEINLINE float GetHealth()      { return Health; }

    FORCEINLINE float GetMaxMana() { return CurrentStatus.MaxMana; }
    FORCEINLINE float GetMana() { return Mana; }

    FORCEINLINE FStatusData GetStatusData() { return CurrentStatus; }

    FORCEINLINE float GetWalkSpeed()   { return CurrentStatus.Speed[(int32)ECharacterSpeed::Walk]; }
    FORCEINLINE float GetRunSpeed()    { return CurrentStatus.Speed[(int32)ECharacterSpeed::Run]; }
    FORCEINLINE float GetSprintSpeed() { return CurrentStatus.Speed[(int32)ECharacterSpeed::Sprint]; }

    FORCEINLINE bool CanMove() { return bCanMove; }
public:	
	UCStatusComponent();

    void AddHealth(float InAmount);
    void SubHealth(float InAmount);

    void AddMana(float InAmount);
    void SubMana(float InAmount);

    void SetMove();
    void SetStop();

    void SetSpeed(ECharacterSpeed InType);

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
