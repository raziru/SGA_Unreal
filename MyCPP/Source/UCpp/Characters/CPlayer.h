// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ICharacter.h"
#include "Components/CActionComponent.h"
#include "Components/CStateComponent.h"//enum can't be Forward Declaration
#include "Components/CInventoryComponent.h"
#include "GenericTeamAgentInterface.h"
#include "CPlayer.generated.h"

UCLASS()
class UCPP_API ACPlayer : public ACharacter, public IICharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()


//Camera
private:
	
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly)
		uint8 TeamId = 0;
//Widget
protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* NameWidget;

	UPROPERTY(VisibleDefaultsOnly)
		class UCUserWidget_Health* StatusWidget;

	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> StatusWidgetClass;

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
		class UCFeetComponent* Feet;

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
	virtual FGenericTeamId GetGenericTeamId() const override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Interact() override;

	virtual void PickUp(class ACItem* InItem) override;

	virtual void OnDefaultMode() override;

	UFUNCTION(BlueprintCallable)
		void BPAddHealth(float InAmount);

	UFUNCTION(BlueprintCallable)
		void BPSubHealth(float InAmount);

	UFUNCTION(BlueprintCallable)
		void BPAddMana(float InAmount);

	UFUNCTION(BlueprintCallable)
		void BPSubMana(float InAmount);

	UFUNCTION(BlueprintCallable)
		void BPAddStatus(FStatusData InStatusData);

//Moving
private:
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);
	void OnZoom(float InAxis);

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

	UFUNCTION()
		void SetOnShield(const bool OnShield);
//Use Consumalbe
	UFUNCTION()
		void SetNewTool(class UCActionData* NewConsumableAction, bool IsConsumable);

	UFUNCTION()
		void EndToolAction();
private:
	void OpenInventory();

private:
	void Begin_Roll();
	void Begin_Backstep();

public:
	void End_Roll();
	void End_Backstep();
private:
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
	UFUNCTION()
		void OnActionTypeChanged(EActionType InPrevType, EActionType InNewType);

	void OnWalk();
	void OffWalk();

	
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

	void UpdateWidget();

public:
	virtual void ChangeColor(FLinearColor InColor) override;
private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;


};
