// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CMontagesComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UCMontagesComponent::UCMontagesComponent()
{
	
}



// Called when the game starts
void UCMontagesComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	CheckNull(DataTable);

	TArray< FMontageData*> datas;
	DataTable->GetAllRows<FMontageData>("", datas);

	/*for (const FMontageData* data : datas)
	{
		if (!!data)
			CLog::Print(data->AnimMontage->GetPathName());
	}*/
	for (int32 i = 0; i < (int32)EStateType::Max; i++)
	{
		for (FMontageData* data : datas)
		{
			if ((EStateType)i == data->Type)
			{
				Datas[i] = data;

				continue;
			}
		}//for(data)
	}//for(i)
}

void UCMontagesComponent::PlayRoll()
{
	PlayAnimMontage(EStateType::Roll);
}

void UCMontagesComponent::PlayBackstep()
{
	PlayAnimMontage(EStateType::Backstep);
}


void UCMontagesComponent::PlayHitted()
{
	PlayAnimMontage(EStateType::Hitted);
}

void UCMontagesComponent::PlayDead()
{
	PlayAnimMontage(EStateType::Dead);
}

void UCMontagesComponent::PlayAnimMontage(EStateType InState)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());

	const FMontageData* data = Datas[(int32)InState];
	if (!!data)
	{
		if (!!data->AnimMontage)
			character->PlayAnimMontage(data->AnimMontage, data->PlayRatio, data->StartSection);
	}
}
