
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"//enum can't be Forward Declaration
#include "CPlayer.generated.h"

UCLASS()
class U03_ACTION_API ACPlayer : public ACharacter
{
	GENERATED_BODY()


private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCMontagesComponent* Montages;
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

private:


	UPROPERTY(VisibleDefaultsOnly)
		class UCOptionComponent* Option;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
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
	void Begin_Roll();	
	void Begin_Backstep();

public:
	void End_Roll();
	void End_Backstep();

};
