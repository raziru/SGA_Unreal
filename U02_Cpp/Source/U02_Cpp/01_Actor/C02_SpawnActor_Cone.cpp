#include "01_Actor/C02_SpawnActor_Cone.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"

AC02_SpawnActor_Cone::AC02_SpawnActor_Cone()
{
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshs/M_Cone.M_Cone'");
	Mesh->SetStaticMesh(mesh);
}

void AC02_SpawnActor_Cone::BeginPlay()
{
	Super::BeginPlay();
	
}


