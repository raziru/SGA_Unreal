#pragma once

#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

class UCPP_API CHelpers//대문자여야야 매크로로 인식한다.
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

	template<typename T>
	static void GetAssetDynamic(T** OutObject, FString InPath)
	{
		T* obj = Cast<T>(StaticLoadObject(T::StaticClass(), NULL, *InPath));
		verifyf(!!obj, L"!!asset");//!! null은 false, null아니면 true
		*OutObject = obj;
	}

	template<typename T>
	static void GetClass(TSubclassOf<T>* OutClass, FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), L"asset.Succeeded()");

		*OutClass = asset.Class;
	}

	template<typename T>
	static void CreateComponent(AActor* InActor, T** InComponent, FName InName, USceneComponent* InParent = NULL)
	{
		*InComponent = InActor->CreateDefaultSubobject<T>(InName);

		if (!!InParent)
		{
			(*InComponent)->SetupAttachment(InParent);

			return;
		}

		InActor->SetRootComponent((*InComponent));
	}
};