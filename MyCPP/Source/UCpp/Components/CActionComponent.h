// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CActionComponent.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Unarmed, Fist, OneHand, TwoHand, Warp, FireStorm, Throw, Max,
};

//delegate는 무조건 public으로 열어줘야 다른쪽에서 사용할 수 있다.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActionTypeChanged, EActionType, InPrevType, EActionType, InNewType);
//Multicast: 함수를 여러개 바인딩해놓을 수 있음 바인딩할 함수는 UFUNCTION이어야 한다.
UCLASS( ClassGroup=(GameProject), meta=(BlueprintSpawnableComponent) )
class UCPP_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
		class UCActionData* Datas[(int32)EActionType::Max];

private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
		class UCActionData* ItemTypeData;

	EActionType ItemActionType;


	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
		class UCActionData* SecondItemTypeData;

	EActionType SecondItemActionType;

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCActionData* GetCurrent() { return Datas[(int32)Type]; }

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnarmedMode() { return Type == EActionType::Unarmed; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsFistMode() { return Type == EActionType::Fist; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsOneHandMode() { return Type == EActionType::OneHand; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsTwoHandMode() { return Type == EActionType::TwoHand; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsWarpMode() { return Type == EActionType::Warp; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsFireStormMode() { return Type == EActionType::FireStorm; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsThrowMode() { return Type == EActionType::Throw; }

public:	
	// Sets default values for this component's properties
	UCActionComponent();
	void SetUnarmedMode();
	void SetFistMode();
	void SetOneHandMode();
	void SetTwoHandMode();
	void SetWarpMode();
	void SetFireStormMode();
	void SetThrowMode();
	void SetItemTypeMode();
	void SetSecondItemTypeMode();

	void OffAllCollision();
	
	void SetNewAction(class UCActionData* NewItemAction, EActionType NewItemActionType);
	void SetNewSecondAction(class UCActionData* NewItemAction, EActionType NewItemActionType);

	void SetOnShield(bool OnNewShield) { OnShield = OnNewShield; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void DoAction();
	void DoActionRelease();

	void DoSecondAction();
	void DoSecondActionRelease();


	void DoAim();
	void OnAim();
	void OffAim();

private:
	void SetAimMode(bool InAim);


private:
	void SetMode(EActionType InType);
	void ChangeType(EActionType InNewType);



public:
	UPROPERTY(BlueprintAssignable)
		FActionTypeChanged OnActionTypeChanged;

private:
	EActionType Type;
	
	bool IsAiming = false;
	bool OnShield = false;
};
