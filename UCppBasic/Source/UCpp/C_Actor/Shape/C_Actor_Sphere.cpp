// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Actor/Shape/C_Actor_Sphere.h"
#include "Global.h"

AC_Actor_Sphere::AC_Actor_Sphere()
{
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshes/M_Sphere.M_Sphere'");
	Mesh->SetStaticMesh(mesh);
}
