#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CArmor.generated.h"

UCLASS()
class UCPP_API ACArmor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACArmor();

protected:
	virtual void BeginPlay() override;

};
