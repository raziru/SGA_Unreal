// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C01_LineTrace.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTraceResult, class AActor*, InActor, FLinearColor, InColor);
UCLASS()
class UCPP_API AC01_LineTrace : public ACharacter
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
public:
	// Sets default values for this character's properties
	AC01_LineTrace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	UFUNCTION()
		void StartJump(class AActor* InActor, FLinearColor InColor);
protected:
	UFUNCTION(BlueprintCallable)
		void RestoreColor(class ACPlayer* InPlayer);
private:
	TArray<class AC01_Cylinder*> Cylinders;

public:
	UPROPERTY(BlueprintAssignable)
		FTraceResult OnTraceResult;
};
