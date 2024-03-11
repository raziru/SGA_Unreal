// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ICharacter.h"
#include "Interact/IInteract.h"
#include "Components/CStateComponent.h"
#include "CEnemy.generated.h"

UCLASS()
class UCPP_API ACEnemy : public ACharacter, public IICharacter, public IIInteract
{
	GENERATED_BODY()


private:
	UPROPERTY(EditAnywhere, Category = "Hitted")
		float LaunchAmount = 100.0f;
protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* NameWidget;

	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* HealthWidget;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UCActionComponent* Action;
	
	UPROPERTY(VisibleDefaultsOnly)
		class UCMontagesComponent* Montages;

	UPROPERTY(VisibleDefaultsOnly)
		class UCPickupComponent* Pickup;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCDialogueComponent* Dialogue;
private:	

	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	
public:
	ACEnemy();

	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void ChangeColor(FLinearColor InColor);

	virtual void Interact(AActor* InOther) override;

	virtual void OnDefaultMode() override;


private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

	UFUNCTION()
		void RestoreColor();

	UFUNCTION()
		void OnUnarmed();

public:
	UFUNCTION()
		void Shout(EStateType InPrevType, EStateType InNewType);

	UFUNCTION()
		void Say(FString Text);

protected:
	void Hitted();
	void Dead();

protected:
	virtual void Begin_Dead() override;
	virtual void End_Dead()   override;

	void Begin_Backstep();
	virtual void End_Backstep();

	UPROPERTY(EditAnywhere)
		EInteractType OwnInteractType;

	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* ShoutWidget;
private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

private:
	class AController* DamageInstigator;
	float DamageValue;
	bool CanPickup;

	
};
