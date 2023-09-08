#include "Framework.h"
#include "MainGame.h"


MainGame::MainGame()
{
	scene = new SolarScene();
}

MainGame::~MainGame()
{
	delete scene;
	Environment::Delete();
	     Device::Delete();


	    Time::Delete();
	Keyboard::Delete();
}

void MainGame::Update()
{
	    Time::GetInstance()->Update();
	Keyboard::GetInstance()->Update();
	scene->Update();
}

void MainGame::Render()
{
	Environment::GetInstance()->Set();
	scene->Render();
}
