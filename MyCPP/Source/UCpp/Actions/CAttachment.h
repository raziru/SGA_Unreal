// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAttachment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentBeginOverlap, class ACharacter*, InAttacker, class AActor*, InAttackCauser, class ACharacter*, InOtherCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentEndOverlap, class ACharacter*, InAttacker, class AActor*, InAttackCauser, class ACharacter*, InOtherCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttachmentCollision);

UENUM(BlueprintType)
enum class EAttachment : uint8
{
	MainHand, SecondHand, Projectile, Max,
};


UCLASS()
class UCPP_API ACAttachment : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USceneComponent* Scene;
protected:
	UFUNCTION(BlueprintCallable)//Can use in blueprint
		void AttachTo(FName InSocketName);

	UFUNCTION(BlueprintCallable)//Can use in blueprint
		void AttachToCollision(class UShapeComponent* InComponent, FName InSocketName);

public:
	FORCEINLINE bool GetIsPress() { return IsPress; }

	FORCEINLINE bool GetIsRightPress() { return IsRightPress; }
public:	
	ACAttachment();

	void OnCollision();
	void OffCollision();
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnEquip();

	UFUNCTION(BlueprintImplementableEvent)
		void OnUnequip();
private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void OnPress(bool InPressAction, bool InPressSecondAction, bool InOnShield);

public:
	UPROPERTY(BlueprintAssignable)
		FAttachmentBeginOverlap OnAttachmentBeginOverlap;

	UPROPERTY(BlueprintAssignable)
		FAttachmentEndOverlap OnAttachmentEndOverlap;

	UPROPERTY(BlueprintAssignable)
		FAttachmentCollision OnAttachmentCollision;

	UPROPERTY(BlueprintAssignable)
		FAttachmentCollision OffAttachmentCollision;
protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;

	UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* Status;

	UPROPERTY(BlueprintReadOnly)
		class UCActionComponent* Action;

private:
	TArray<class UShapeComponent*> ShapeComponents;//충돌체 형태를 자유롭게 쓰기위함

	bool IsPress; 
	bool IsRightPress;
};
