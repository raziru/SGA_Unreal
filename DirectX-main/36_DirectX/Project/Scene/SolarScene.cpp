#include "Framework.h"
#include "SolarScene.h"

SolarScene::SolarScene()
{
	sun = new Sun;
}

SolarScene::~SolarScene()
{
	delete sun;
}

void SolarScene::Update()
{

	
	sun->Update();
}

void SolarScene::Render()
{
	sun->Render();
}
