// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ICharacter.h"
#include "Components/CStateComponent.h"//enum can't be Forward Declaration
#include "Components/CInventoryComponent.h"
#include "CPlayer.generated.h"

UCLASS()
class UCPP_API ACPlayer : public ACharacter, public IICharacter
{
	GENERATED_BODY()


//Camera
private:
	
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

//Interact
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* InteractBox;

//Components
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UCActionComponent* Action;

	UPROPERTY(VisibleDefaultsOnly)
		class UCTargetComponent* Target;

	UPROPERTY(VisibleDefaultsOnly)
		class UCMontagesComponent* Montages;

	UPROPERTY(VisibleDefaultsOnly)
		class UCOptionComponent* Option;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCInventoryComponent* Inventory;

	UPROPERTY(VisibleDefaultsOnly)
		class UCInteractComponent* Interaction;

	UPROPERTY(VisibleDefaultsOnly)
		class UCEquipComponent* Equipment;

public:
	FORCEINLINE class UCUserWidget_ActionList* GetActionList() { return Action->GetActionList(); }

//Widget
protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* EquipWidget;
public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Interact() override;

	virtual void PickUp(class ACItem* InItem) override;

	virtual void OnDefaultMode() override;
//Moving
private:
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);

private:
	void OnAvoid();

private:
//Weapon Equip
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);
	UFUNCTION()
		void SetNewItem(const FItemData NewItem);
	UFUNCTION()
		void SetNewMainWeapon(class UCActionData* NewItemAction, EActionType NewItemActionType);
	UFUNCTION()
		void SetOnShield(bool IsShield);
	UFUNCTION()
		void EquipSecond(EActionType InActionType);
	UFUNCTION()
		void UnequipSecond(EActionType InActionType);

//Armor Equip
	UFUNCTION()
		void SetNewArmor(TSubclassOf<class ACArmor> NewArmor);

	UFUNCTION()
		void SetNewStatus(const FStatusData NewStatus);

	UFUNCTION()
		void ResfreshStatus(const FStatusData NewStatus);
//Use Consumalbe
	UFUNCTION()
		void SetNewConsumable(class UCActionData* NewConsumableAction);
private:
	void OpenInventory();

private:
	void Begin_Roll();
	void Begin_Backstep();

public:
	void End_Roll();
	void End_Backstep();
private:
	/*void OnFist();
	void OnOneHand();
	void OnTwoHand();
	void OnWarp();
	void OnFireStorm();
	void OnThrow();*/

	UFUNCTION()
		void OnUnarmed();
	UFUNCTION()
		void OnFist();
	UFUNCTION()
		void OnOneHand();
	UFUNCTION()
		void OnTwoHand();
	UFUNCTION()
		void OnWarp();
	UFUNCTION()
		void OnFireStorm();
	UFUNCTION()
		void OnThrow();


	
	void OnMainWeapon();

	void OnDoAction();
	void OnDoActionRelease();

	void OnDoSecondAction();
	void OnDoSecondActionRelease();


	void OnTarget();
	void OnTargetLeft();
	void OnTargetRight();

	void OnAim();
	void OffAim();

	void OnViewActionList();
	void OffViewActionList();

	void OnTool();

public:
	virtual void ChangeColor(FLinearColor InColor) override;
private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;


};
