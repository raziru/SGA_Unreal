

#include "03_Collision/C07_SpotLight.h"
#include "Global.h"
#include "C05_MulticastTrigger.h"
#include "Components/TextRenderComponent.h"
#include "Components/SpotLightComponent.h"

//delegate는 블프와 통신이 가능하다. event는 외부호출 내부 실행이라 c내부에서만 내용이 교환된다.
AC07_SpotLight::AC07_SpotLight()
{
   CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
   CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

   Text->SetRelativeLocation(FVector(0, 0, 100));
   Text->SetRelativeRotation(FRotator(0, 180, 0));
   Text->SetRelativeScale3D(FVector(2));
   Text->TextRenderColor = FColor::Red;
   Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
   Text->Text = FText::FromString(GetName());

   for (int32 i = 0; i < 3; i++)
   {
      FString str;
      str.Append("SpotLights_");
      str.Append(FString::FromInt(i + 1));

      CHelpers::CreateComponent<USpotLightComponent>(this, &SpotLights[i], FName(str), Scene);

      SpotLights[i]->SetRelativeLocation(FVector(0, i * 150, 0));
      SpotLights[i]->SetRelativeRotation(FRotator(-90, 0, 0));
      SpotLights[i]->Intensity = 1e+5f;
      SpotLights[i]->OuterConeAngle = 25.0f;
   }

}

void AC07_SpotLight::BeginPlay()
{
	Super::BeginPlay();
    TArray<AC05_MultiCastTrigger*> triggers;
    CHelpers::FindActors<AC05_MultiCastTrigger>(GetWorld(), triggers);
    triggers[0]->OnMultiLightBeginOverlap.AddUFunction(this, "OnLightColor");
}

void AC07_SpotLight::OnLightColor(int32 InIndex, FLinearColor InColor)
{
    for (int32 i = 0; i < 3; i++)
        SpotLights[i]->SetLightColor(FLinearColor(1, 1, 1));

    SpotLights[InIndex]->SetLightColor(InColor);
}



