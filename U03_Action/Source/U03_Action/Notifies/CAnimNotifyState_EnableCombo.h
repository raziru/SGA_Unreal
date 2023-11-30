
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState_EnableCombo.generated.h"

//마지막 콤보동작에는 넣으면 안된다.
UCLASS()
class U03_ACTION_API UCAnimNotifyState_EnableCombo : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	FString GetNotifyName_Implementation() const override;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
