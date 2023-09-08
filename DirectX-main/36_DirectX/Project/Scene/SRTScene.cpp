#include "Framework.h"
#include "SRTScene.h"


SRTScene::SRTScene()
{
    object = new Object();

    world = XMMatrixIdentity();

    worldBuffer = new MatrixBuffer();

    S = {};
    R = {};
    T = {};
}

SRTScene::~SRTScene()
{
    delete object;
    delete worldBuffer;

}



void SRTScene::Update()
{
    S = XMMatrixScaling(scale.x, scale.y, 1.0f);
    R = XMMatrixRotationZ(angle);
    T = XMMatrixTranslation(translation.x, translation.y, 0.0f);


    world = S * R * T;

    //world2 = XMMatrixTranslation(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f,0) ;

    //world *= world2;//world 1이 world2의 세계로 넘어감, 부모(world2) 자식(world)관계

    //중심이 될 오브젝트의 SRT를 받아서 뒤에 곱하면 이동축이 바뀌게된다-> 태양의 SRT를 받자.
}


void SRTScene::Render()
{

    worldBuffer->SetData(world);
    worldBuffer->VSSetBuffer(0);
    object->Render();//draw call


    //worldBuffer->SetData(world2);
    //worldBuffer->VSSetBuffer(0);
    //object->Render();//draw call

}