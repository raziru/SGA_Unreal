
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Dialogue.generated.h"

UCLASS()
class UCPP_API UCUserWidget_Dialogue : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void Update(const FString& Name, const FString& Text);
};
