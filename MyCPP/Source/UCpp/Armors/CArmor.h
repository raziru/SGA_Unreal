#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CStatusComponent.h"
#include "CArmor.generated.h"

UENUM(BlueprintType)
enum class EArmorType : uint8
{
	Weapon, Helmet, Top, Bottom, Shoes, Hands, Shield, Max,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FArmorAttachmentDelegate, FStatusData, ArmorStatus);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FArmorDetachmentDelegate, FStatusData, ArmorStatus);

UCLASS()
class UCPP_API ACArmor : public AActor
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
		virtual void Attachment(class ACharacter* OwnerCharacter) {}
	UFUNCTION(BlueprintCallable)
		virtual void Detachment() {}

public:
	UFUNCTION(BlueprintImplementableEvent)
		void Equip(class ACharacter* OwnerCharacter);
	UFUNCTION(BlueprintImplementableEvent)
		void UnEquip();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
		FArmorAttachmentDelegate OnAttachmentDelegate;

	UPROPERTY(BlueprintAssignable)
		FArmorDetachmentDelegate OnDetachmentDelegate;

};
