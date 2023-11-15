// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Actor/C02_SpawnActor_Sphere.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"

AC02_SpawnActor_Sphere::AC02_SpawnActor_Sphere()
{
	UStaticMesh * mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshes/M_Sphere.M_Sphere'");
	Mesh->SetStaticMesh(mesh);
}

void AC02_SpawnActor_Sphere::BeginPlay()
{
	Super::BeginPlay();
	
}


