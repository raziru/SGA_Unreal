// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CHUDStatus.generated.h"

/**
 * 
 */
UCLASS()
class UCPP_API ACHUDStatus : public AHUD
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly)
		class UTexture2D* Texture;

public:
	FORCEINLINE void SetDrawMode() { bDraw = true; }
	FORCEINLINE void SetUndrawMode() { bDraw = false; }


private:
	bool bDraw;
};
