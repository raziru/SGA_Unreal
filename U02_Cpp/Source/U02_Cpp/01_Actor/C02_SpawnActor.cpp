#include "01_Actor/C02_SpawnActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInstanceConstant.h"

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
	CHelpers::GetAsset<UStaticMesh>(&mesh,"StaticMesh'/Game/Meshes/M_Cube.M_Cube'" );
	Mesh->SetStaticMesh(mesh);
}

void AC02_SpawnActor::BeginPlay()
{
	Super::BeginPlay();

	//MaterialInstanceConstant'/Game/Materials/M_Mesh_Inst.M_Mesh_Inst'
	/*UObject* obj = StaticLoadObject(UMaterialInstanceConstant::StaticClass(),
		NULL, L"MaterialInstanceConstant'/Game/Materials/M_Mesh_Inst.M_Mesh_Inst'");
	UMaterialInstanceConstant* material = Cast<UMaterialInstanceConstant>(obj);*/

	UMaterialInstanceConstant* material;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&material,
		"MaterialInstanceConstant'/Game/Materials/M_Mesh_Inst.M_Mesh_Inst'");
	Material = UMaterialInstanceDynamic::Create(material, this);
	Mesh->SetMaterial(0, Material);

	UKismetSystemLibrary::K2_SetTimer(this, "ChangeColor", 1.0f, true);

}

void AC02_SpawnActor::ChangeColor()
{
	FLinearColor color;
	color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.A = 1.0f;

	Material->SetVectorParameterValue("Color", color);
}



