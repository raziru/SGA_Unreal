// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Melee.generated.h"


UCLASS()
class UCPP_API ACDoAction_Melee : public ACDoAction
{
	GENERATED_BODY()

public:
	FORCEINLINE void EnableCombo() { bEnable = true; }
	FORCEINLINE void DisableCombo() { bEnable = false; }
public:
	virtual void DoAction()       override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction()   override;

public:

	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;
	//unarmed를 쓴다면 무조건 재정의를 안할수도 있기 때문에 {}을 써서 빈공간으로 남긴다.
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;
	virtual void OnAttachmentCollision() override;
	virtual void OffAttachmentCollision() override;

private:
	bool bExist;
	bool bEnable;
	bool bLast;

	int32 Index;
};
