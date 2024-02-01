#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actions/CAttachment.h"
#include "Components/CStatusComponent.h"
#include "CArmor.generated.h"

UENUM(BlueprintType)
enum class EArmorType : uint8
{
	Weapon, Helmet, Top, Bottom, Shoes, Hands, Shield, Max,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FArmorAttach, FStatusData, ArmorStatus);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FArmorDetach, FStatusData, ArmorStatus);

UCLASS()
class UCPP_API ACArmor : public ACAttachment
{
	GENERATED_BODY()

public:
	FORCEINLINE FStatusData GetStatusData() { return StatusData; }
	FORCEINLINE EArmorType  GetArmorType()  { return ArmorType; }
	FORCEINLINE FName GetName() { return Name; }

protected:
	UPROPERTY(EditAnywhere)
		FStatusData StatusData;

	UPROPERTY(EditAnywhere)
		EArmorType ArmorType;

	UPROPERTY(EditAnywhere)
		FName Name;


public:	
	ACArmor();


public:
	UFUNCTION(BlueprintCallable)
		virtual void Attach() {}
	UFUNCTION(BlueprintCallable)
		virtual void Detach() {}
	UFUNCTION(BlueprintCallable)
		virtual void MoveTo(FName InSocket) {}



protected: 
	ACharacter* OwnerCharacter;	
	
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
		FArmorAttach OnAttach;

	UPROPERTY(BlueprintAssignable)
		FArmorDetach OnDetach;

};
