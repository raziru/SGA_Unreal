

#include "03_Collision/C06_Box.h"
#include "Global.h"
#include "C05_MulticastTrigger.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"


AC06_Box::AC06_Box()
{
CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
   CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

   Text->SetRelativeLocation(FVector(0, 0, 100));
   Text->SetRelativeRotation(FRotator(0, 180, 0));
   Text->SetRelativeScale3D(FVector(2));
   Text->TextRenderColor = FColor::Red;
   Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
   Text->Text = FText::FromString(GetName());


   UStaticMesh* mesh;
   CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshes/M_Cube.M_Cube'");
   for (int32 i = 0; i < 3; i++)
   {
      FString str;
      str.Append("Mesh_");
      str.Append(FString::FromInt(i + 1));

      CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh[i], FName(str), Scene);

      Mesh[i]->SetRelativeLocation(FVector(0, i * 150, 0));
      Mesh[i]->SetStaticMesh(mesh);
      Mesh[i]->SetSimulatePhysics(false);
   }
}

void AC06_Box::BeginPlay()
{
	Super::BeginPlay();
    TArray<AC05_MultiCastTrigger*> triggers;
    CHelpers::FindActors<AC05_MultiCastTrigger>(GetWorld(), triggers);

    triggers[0]->OnMultiLightBeginOverlap.AddUFunction(this, "OnPhysics");

    UMaterialInstanceConstant* material;
    CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/Materials/M_Mesh_Inst.M_Mesh_Inst'");

    for (int32 i = 0; i < 3; i++)
    {
        Materials[i] = UMaterialInstanceDynamic::Create(material, this);
        Mesh[i]->SetMaterial(0, Materials[i]);

        FTransform transform = Mesh[i]->GetComponentToWorld();
        WorldLocation[i] = transform.GetLocation();
    }

}

void AC06_Box::OnPhysics(int32 InIndex, FLinearColor InColor)
{
    for (int32 i = 0; i < 3; i++)
    {
        Materials[i]->SetVectorParameterValue("Color", FLinearColor(1, 1, 1));

        Mesh[i]->SetSimulatePhysics(false);
        Mesh[i]->SetWorldLocation(WorldLocation[i]);
    }

    Materials[InIndex]->SetVectorParameterValue("Color", InColor);
    Mesh[InIndex]->SetSimulatePhysics(true);
}



