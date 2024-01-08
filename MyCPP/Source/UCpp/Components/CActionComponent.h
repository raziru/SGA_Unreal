// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CActionComponent.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Unarmed, Fist, OneHand, TwoHand, Warp, FireStorm, Throw, Bow, Tool, Max,
};

//delegate는 무조건 public으로 열어줘야 다른쪽에서 사용할 수 있다.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActionTypeChanged, EActionType, InPrevType, EActionType, InNewType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActionPress, bool, InPressAction, bool, InPressSecondAction, bool, InOnShield);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEquipSecond, EActionType, InActionType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUnequipSecond, EActionType, InActionType);

//Multicast: 함수를 여러개 바인딩해놓을 수 있음 바인딩할 함수는 UFUNCTION이어야 한다.
UCLASS( ClassGroup=(GameProject), meta=(BlueprintSpawnableComponent) )
class UCPP_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
		class UCActionData* Datas[(int32)EActionType::Max];
private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UCUserWidget_ActionList> ActionListClass;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
		class UCActionData* MainWeaponData;

	EActionType MainWeaponType;


	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
		class UCActionData* SecondWeaponData;

	EActionType SecondWeaponType;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
		class UCActionData* ToolAction;

	class ACPlayer* Player; 

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCActionData* GetCurrent() { return Datas[(int32)Type]; }

public:
	UFUNCTION()
		FORCEINLINE class UCUserWidget_ActionList* GetActionList() { return ActionList; }

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

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsToolMode() { return Type == EActionType::Tool; }


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
	void SetMainWeaponMode();
	void SetSecondWeaponMode();
	void SetToolMode();


	void OffAllCollision();
	
	void SetNewMainWeapon(class UCActionData* NewItemAction, EActionType NewItemActionType);

	void SetNewSecondWeapon(class UCActionData* NewItemAction, EActionType NewItemActionType);

	void SetNewToolAction(class UCActionData* NewToolAction);

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

	void OnViewActionList();
	void OffViewActionList();



private:
	void SetAimMode(bool InAim);

	UFUNCTION()
		void ActionPress(bool InPressAction, bool InPressSecondAction);

	UFUNCTION()
		void OnSecondEquip();

	UFUNCTION()
		void OffSecondEquip();

	UFUNCTION()
		void EndToolAction();
private:
	void SetMode(EActionType InType);
	void ChangeType(EActionType InNewType);
	void ActionBeginPlay(class UCActionData* NewAction);
public:
	UPROPERTY(BlueprintAssignable)
		FActionTypeChanged OnActionTypeChanged;
	UPROPERTY(BlueprintAssignable)
		FOnActionPress OnActionPress;
	UPROPERTY(BlueprintAssignable)
		FEquipSecond EquipSecond;

	UPROPERTY(BlueprintAssignable)
		FUnequipSecond UnequipSecond;

private:
	EActionType Type;

	EActionType PrevType;

	ACharacter* Owner;
	
	bool IsAiming = false;
	bool OnShield = false;
	bool OnGuard  = false;

private:
	class UCUserWidget_ActionList* ActionList;
};
