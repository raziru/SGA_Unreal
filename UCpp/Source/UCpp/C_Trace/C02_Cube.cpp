// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Trace/C02_Cube.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
AC02_Cube::AC02_Cube()
{
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh");

	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshes/M_Cube.M_Cube'");
	Mesh->SetStaticMesh(mesh);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);

}

// Called when the game starts or when spawned
void AC02_Cube::BeginPlay()
{
	Super::BeginPlay();
	
}



