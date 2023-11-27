// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Actor/Shape/C_Actor_Cube.h"
#include "Global.h"
AC_Actor_Cube::AC_Actor_Cube()
{
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshes/M_Cube.M_Cube'");
	Mesh->SetStaticMesh(mesh);
}
