// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Actor/Shape/C_Actor_Cone.h"
#include "Global.h"

AC_Actor_Cone::AC_Actor_Cone()
{
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshs/M_Cone.M_Cone'");
	Mesh->SetStaticMesh(mesh);
}
