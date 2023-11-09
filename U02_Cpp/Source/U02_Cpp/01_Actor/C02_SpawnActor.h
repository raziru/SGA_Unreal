#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_SpawnActor.generated.h"

UCLASS()
class U02_CPP_API AC02_SpawnActor : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

public:	
	AC02_SpawnActor();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void ChangeColor();
private:
	class UMaterialInstanceDynamic* Material;

};
