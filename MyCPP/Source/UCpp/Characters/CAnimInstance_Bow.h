
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance_Bow.generated.h"

UCLASS()
class UCPP_API UCAnimInstance_Bow : public UAnimInstance
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool IsPulled;
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
