// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actions/CActionData.h"
#include "CDoAction.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActionPress, bool, InPressAction, bool, InPressSecondAction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndAction);
UCLASS()
class UCPP_API ACDoAction : public AActor
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetDatas(TArray<FDoActionData> InDatas) { Datas = InDatas; }
	FORCEINLINE void SetEquipped(const bool* InEquipped) { bEquipped = InEquipped; }

public:	
	// Sets default values for this actor's properties
	ACDoAction();
public:
	virtual void DoAction() {}
	virtual void Begin_DoAction() {}
	virtual void End_DoAction() {}

	virtual void DoActionRelease() {}
	virtual void Begin_DoActionRelease() {}
	virtual void End_DoActionRelease() {}

	virtual void DoSecondAction() {}
	virtual void Begin_DoSecondAction() {}
	virtual void End_DoSecondAction() {}

	virtual void DoSecondActionRelease() {}
	virtual void Begin_DoSecondActionRelease() {}
	virtual void End_DoSecondActionRelease() {}

	virtual void OnAim(){}
	virtual void OffAim() {}

public:
	UFUNCTION()
		virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) {}
	//unarmed�� ���ٸ� ������ �����Ǹ� ���Ҽ��� �ֱ� ������ {}�� �Ἥ ��������� �����.
	UFUNCTION()
		virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) {}
	UFUNCTION()
		virtual void OnAttachmentCollision() {}
	UFUNCTION()
		virtual void OffAttachmentCollision() {}


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void DestroyAll();
protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;

	UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* Status;

public:
	UPROPERTY(BlueprintAssignable)
		FActionPress ActionPress;

	UPROPERTY(BlueprintAssignable)
		FEndAction EndAction;

protected:
	bool PressDoAction;
	bool PressDoSecondAction;
	const bool* bEquipped;
	TArray<FDoActionData> Datas;
};
