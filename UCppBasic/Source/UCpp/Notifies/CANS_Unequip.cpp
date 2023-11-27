
#include "Notifies/CANS_Unequip.h"
#include "Global.h"
#include "Interface/IRifle.h"
#include "Weapons/CRifle.h"

FString UCANS_Unequip::GetNotifyName_Implementation() const
{
	return "Unequip";
}

void UCANS_Unequip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);

	IIRifle* rifle = Cast<IIRifle>(MeshComp->GetOwner());
	CheckNull(rifle);

	rifle->GetRifle()->Begin_Unequip();
}

void UCANS_Unequip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);

	IIRifle* rifle = Cast<IIRifle>(MeshComp->GetOwner());
	CheckNull(rifle);

	rifle->GetRifle()->End_Unequip();
}