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

//delegate�� ������ public���� ������� �ٸ��ʿ��� ����� �� �ִ�.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActionTypeChanged, EActionType, InPrevType, EActionType, InNewType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActionPress, bool, InPressAction, bool, InPressSecondAction, bool, InOnShield);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEquipSecond, EActionType, InActionType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUnequipSecond, EActionType, InActionType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndToolAction);

//Multicast: �Լ��� ������ ���ε��س��� �� ���� ���ε��� �Լ��� UFUNCTION�̾�� �Ѵ�.
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
	UPROPERTY(EditDefaultsOnly)
		class UCActionData* UnarmedData;
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
	UFUNCTION(BlueprintCallable)
		void SetUnarmedMode();
	UFUNCTION(BlueprintCallable)
		void SetOneHandMode();
	UFUNCTION(BlueprintCallable)
		void SetTwoHandMode();

	void SetFistMode();
	void SetWarpMode();
	void SetFireStormMode();
	void SetThrowMode();
	void SetMainWeaponMode();
	void SetSecondWeaponMode();
	void SetToolMode();


	void OffAllCollision();
	
	void SetNewMainWeapon(class UCActionData* NewItemAction, EActionType NewItemActionType);

	void SetNewSecondWeapon(class UCActionData* NewItemAction, EActionType NewItemActionType);

	void SetNewTool(class UCActionData* NewToolAction, bool IsConsumable);


	UFUNCTION()
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
		void EndTool();
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

	UPROPERTY(BlueprintAssignable)
		FEndToolAction EndToolAction;

private:
	EActionType Type;

	EActionType PrevType;

	ACharacter* Owner;


	
	bool IsAiming = false;
	bool OnShield = false;
	bool OnGuard  = false;

	bool IsConsumableTool = false;

private:
	class UCUserWidget_ActionList* ActionList;
};
