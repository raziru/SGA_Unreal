

#include "CThrow_Arrow.h"
#include "Global.h"
#include "Components/SphereComponent.h"

ACThrow_Arrow::ACThrow_Arrow()
{
	CHelpers::CreateComponent<USphereComponent>(this, &Sphere, "Sphere");
	//CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh");
}
