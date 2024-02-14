// Fill out your copyright notice in the Description page of Project Settings.


#include "CHUD.h"
#include "Global.h"
#include "Engine/Texture2D.h"
#include "Engine/Canvas.h"

ACHUD::ACHUD()
{
	CHelpers::GetAsset<UTexture2D>(&Texture, "Texture2D'/Game/Textures/T_Crosshair.T_Crosshair'");
}

void ACHUD::DrawHUD()
{
	Super::DrawHUD();
	CheckFalse(bDraw);
	
	CheckNull(Texture);

	FVector2D center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	FVector2D size(Texture->GetSurfaceWidth() * 0.5f, Texture->GetSurfaceHeight() * 0.5f);
	FVector2D position = center - size;

	FCanvasTileItem item(position, Texture->Resource, FLinearColor::White);//타일처럼 위치에 까는 것
	item.BlendMode = SE_BLEND_Translucent;//일정 투명값이하는 제거하여 blend하는 것

	Canvas->DrawItem(item);
}
