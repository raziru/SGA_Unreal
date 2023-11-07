#pragma once

#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

class U02_CPP_API CHelpers
{
public:
	template<typename T>
	static void GetAsset(T** OutObject, FString Inpath)
	{
		ConstructorHelpers::FObjectFinder<T> 
			asset(*Inpath);
		verifyf(asset.Succeeded(), L"asset.Succeeded()");//== assert


		*OutObject = asset.Object;
	}
};