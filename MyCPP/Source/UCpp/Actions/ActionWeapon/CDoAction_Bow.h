
#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Bow.generated.h"


UCLASS()
class UCPP_API ACDoAction_Bow : public ACDoAction
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

	virtual void DoActionRelease() override;
	virtual void Begin_DoActionRelease() override;
	virtual void End_DoActionRelease() override;

	virtual void DoSecondAction() override;
	virtual void DoSecondActionRelease() override;

	virtual void OnAim() override;
	virtual void OffAim() override;

	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void OnThrowBeginOverlap(FHitResult InHitResult);

private:
	class UCAim* Aim;
};
