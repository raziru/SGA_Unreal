#include "01_Actor/C02_SpawnActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"

AC02_SpawnActor::AC02_SpawnActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>
		("Mesh");
	RootComponent = Mesh;
	//StaticMesh'/Game/Meshs/M_Cube.M_Cube'--  prefer reference 
	//D:/202309Unreal/UnrealEngine/U02_Cpp/Content/Meshs/M_Cube.uasset

	//ConstructorHelpers::FObjectFinder<UStaticMesh> mesh
	//(
	//	L"StaticMesh'/Game/Meshs/M_Cube.M_Cube'"
	//);
	//if (mesh.Succeeded())//if construct, must check
	//{
	//	Mesh->SetStaticMesh(mesh.Object);
	//}

	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh,"StaticMesh'/Game/Meshs/M_Cube.M_Cube'" );
	Mesh->SetStaticMesh(mesh);
}

void AC02_SpawnActor::BeginPlay()
{
	Super::BeginPlay();
	
}



