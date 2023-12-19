
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CInteract.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractBeginOverlap, class AActor*, InInteracted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractEndOverlap,   class AActor*, InInteracted);

UCLASS()
class UCPP_API ACInteract : public AActor
{
	GENERATED_BODY()
	
public:	
	ACInteract();

	UFUNCTION(BlueprintCallable)//Can use in blueprint
		void AttachToCollision(class UShapeComponent* InComponent, FName InSocketName);

protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere)
		class UShapeComponent* InteractBox;

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	UPROPERTY(BlueprintAssignable)
		FInteractBeginOverlap OnInteractBeginOverlap;

	UPROPERTY(BlueprintAssignable)
		FInteractEndOverlap   OnInteractEndOverlap;


protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

private:
	TArray<class UShapeComponent*> Interactions;
};
