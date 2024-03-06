
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Shout.generated.h"


UCLASS()
class UCPP_API UCUserWidget_Shout : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void Update(const FString& Text);
	
};
