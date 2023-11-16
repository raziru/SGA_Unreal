#pragma once

#include "CoreMinimal.h"
#include "IRifle.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

UCLASS()
class U02_CPP_API ACPlayer : public ACharacter, public IIRifle
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

public:
	FORCEINLINE class ACRifle* GetRifle() override { return Rifle; }

public:
	ACPlayer();


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	void OnHorizontalLook(float Axis);
	void OnVerticalLook(float Axis);
private:
	void OnRunning();
	void OffRunning();

	void OnRifle();


public:
	UFUNCTION(BlueprintCallable)
		void ChangeColor(FLinearColor InColor);
private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

private:
	class ACRifle* Rifle;
};
