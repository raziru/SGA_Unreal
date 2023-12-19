// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ICharacter.h"
#include "Components/CStateComponent.h"//enum can't be Forward Declaration
#include "CPlayer.generated.h"

UCLASS()
class UCPP_API ACPlayer : public ACharacter, public IICharacter
{
	GENERATED_BODY()

private:
	
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* InteractBox;




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
public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Interact() override;

	virtual void PickUp(class ACItem* InItem) override;
	
private:
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);

private:
	void OnAvoid();

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);


private:
	void OpenInventory();

private:
	void Begin_Roll();
	void Begin_Backstep();

public:
	void End_Roll();
	void End_Backstep();
private:
	void OnFist();
	void OnOneHand();
	void OnTwoHand();
	void OnWarp();
	void OnFireStorm();

	void OnDoAction();

	void OnTarget();
	void OnTargetLeft();
	void OnTargetRight();
public:
	virtual void ChangeColor(FLinearColor InColor) override;
private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;
};