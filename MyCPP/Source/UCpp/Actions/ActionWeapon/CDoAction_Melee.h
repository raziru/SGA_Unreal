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

	virtual void DoSecondAction() override;
	virtual void DoSecondActionRelease() override;
public:

	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;
	//unarmed�� ���ٸ� ������ �����Ǹ� ���Ҽ��� �ֱ� ������ {}�� �Ἥ ��������� �����.
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;
	virtual void OnAttachmentCollision() override;
	virtual void OffAttachmentCollision() override;


private:
	UFUNCTION()
		void RestoreDilation();
private:
	bool bExist;
	bool bEnable;
	bool bLast;

	int32 Index;

	TArray<class ACharacter*> HittedCharacters;
};
