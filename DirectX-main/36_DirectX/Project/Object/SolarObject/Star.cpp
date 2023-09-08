#include "Framework.h"
#include "Star.h"

Star::Star()
{
    object = new Object();

    world = XMMatrixIdentity();

    parentWorld = XMMatrixIdentity();

    worldBuffer = new MatrixBuffer();

    

    S = {};
    R = {};
    T = {};
}

Star::~Star()
{
    delete object;
    delete worldBuffer;
}

void Star::Update()
{
    //translation = WIN_CENTER;
    
    angle += (dir) * Time::Delta();


    S = XMMatrixScaling(scale.x, scale.y, 1.0f);
    R = XMMatrixRotationZ(angle);
    T = XMMatrixTranslation(translation.x, translation.y, 0.0f);


    world = S * R * T * parentWorld;
}

void Star::Render()
{
    worldBuffer->SetData(world);
    worldBuffer->VSSetBuffer(0);
    object->Render();//draw call
}
