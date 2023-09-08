#include "Framework.h"
#include "Sun.h"


Sun::Sun()
{
}

Sun::~Sun()
{
}

void Sun::Update()
{
	translation = WIN_CENTER;
	angle += Time::Delta();
	Star::Update();
}

void Sun::Render()
{
}
