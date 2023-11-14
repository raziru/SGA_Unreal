
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C03_Trigger.generated.h"


//delegate�� �Լ��� �̸� ��� ���� �ּҸ� ������ ������ ��ٸ�
//�Լ��� ����ϱ� ���� ��ü�� �����ϴ� ��� delegate�� �Լ��� ���ͼ� ����Ѵ�.
//������ �Ұ�� �� ��ü�� ���յ��� Ŀ���� �� ��ü�� �̻��� ����� �ٰ��� ���峭��.
//A has B ����(���� ����)�� ���� ���յ� ������ �����ؾ��ϴ� �����̴�.
DECLARE_DELEGATE(FBoxLightBeginOverlap); //void __(void) using delegate same as function pointer in c++
DECLARE_DELEGATE(FBoxLightEndOverlap); //void __(void)
DECLARE_DELEGATE_RetVal_OneParam(FString, FBoxLightRandomBeginOverlap, FLinearColor);
//multi cast �ټ��� ����ȯ�� ���ÿ� �����ϴ� ���̴�.

UCLASS()
class U02_CPP_API AC03_Trigger : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
public:	
	AC03_Trigger();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

public://Delegate�� ������� �͵� �����ؾ� ��밡��, public���� ������� ��밡��
	FBoxLightBeginOverlap OnBoxLightBeginOverlap;
	FBoxLightEndOverlap OnBoxLightEndOverlap;
	FBoxLightRandomBeginOverlap OnBoxLightRandomBeginOverlap;
};
