#include "Framework.h"
#include "SolarScene.h"

SolarScene::SolarScene()
{
	sun     = new Star;
	mecury  = new Star;
	venus   = new Star;
	earth   = new Star;
	mars    = new Star;
	jupiter = new Star;
	saturn  = new Star;
	uranus  = new Star;
	neptune = new Star;
	pluto   = new Star;

}

SolarScene::~SolarScene()
{

	delete sun    ;
	delete mecury ;
	delete venus  ;
	delete earth  ;
	delete mars   ;
	delete jupiter;
	delete saturn ;
	delete uranus ;
	delete neptune;
	delete pluto  ;
}

void SolarScene::Update()
{
	sun->Scale() = { 0.7,0.7 };
	sun->Translation() = WIN_CENTER;


	mecury->Scale() = { 0.3,0.3 };
	mecury->Translation() = { 150,0 };
	mecury->SetParent() = sun->GetWorld();


	venus->Scale() = { 0.5,0.5 };
	venus->Dir() = -1.0f;
	venus->Translation() = { 250,0 };
	venus->SetParent() = sun->GetWorld();






	sun    ->Update();
	mecury ->Update();
	venus  ->Update();
	earth  ->Update();
	mars   ->Update();
	jupiter->Update();
	saturn ->Update();
	uranus ->Update();
	neptune->Update();
	pluto  ->Update();
}

void SolarScene::Render()
{
	
	

	sun    ->Render();
	mecury ->Render();
	venus  ->Render();
	earth  ->Render();
	mars   ->Render();
	jupiter->Render();
	saturn ->Render();
	uranus ->Render();
	neptune->Render();
	pluto  ->Render();
}
