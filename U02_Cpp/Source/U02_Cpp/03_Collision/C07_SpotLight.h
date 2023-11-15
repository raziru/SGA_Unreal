
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C07_SpotLight.generated.h"

UCLASS()
class U02_CPP_API AC07_SpotLight : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

	UPROPERTY(VisibleDefaultsOnly)
		class USpotLightComponent* SpotLights[3];
public:	
	AC07_SpotLight();

protected:
	virtual void BeginPlay() override;
private:
	UFUNCTION()
		void OnLightColor(int32 InIndex, FLinearColor InColor);


};
