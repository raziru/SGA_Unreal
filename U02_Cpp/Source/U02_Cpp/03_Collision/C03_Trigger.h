
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C03_Trigger.generated.h"


//delegate로 함수를 미리 묶어서 누가 주소를 보내줄 때까지 기다림
//함수를 사용하기 위해 객체를 소유하는 대신 delegate로 함수만 빼와서 사용한다.
//소유를 할경우 두 객체간 결합도가 커져서 한 객체가 이상이 생기면 다같이 고장난다.
//A has B 관계(소유 관계)는 높은 결합도 때문에 지향해야하는 구조이다.
DECLARE_DELEGATE(FBoxLightBeginOverlap); //void __(void) using delegate same as function pointer in c++
DECLARE_DELEGATE(FBoxLightEndOverlap); //void __(void)
DECLARE_DELEGATE_RetVal_OneParam(FString, FBoxLightRandomBeginOverlap, FLinearColor);
//multi cast 다수의 형변환을 동시에 진행하는 것이다.

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

public://Delegate로 만들어진 것도 선언해야 사용가능, public으로 열어줘야 사용가능
	FBoxLightBeginOverlap OnBoxLightBeginOverlap;
	FBoxLightEndOverlap OnBoxLightEndOverlap;
	FBoxLightRandomBeginOverlap OnBoxLightRandomBeginOverlap;
};
