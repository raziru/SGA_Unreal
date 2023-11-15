
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C10_Override.generated.h"

UCLASS()
class U02_CPP_API AC10_Override : public AActor
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
	AC10_Override();

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintImplementableEvent)//몸체없이 블프에서 정의가능, 순수 가상함수처럼 작동
		void ChangeColorRed();

	UFUNCTION(BlueprintNativeEvent)
		void ChangeColorWhite();
	void ChangeColorWhite_Implementation();//가상함수의 기본 정의를 하는 과정 
	//재정의시 c에서 정의한 것은 무시된다.
private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
