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

    //world *= world2;//world 1�� world2�� ����� �Ѿ, �θ�(world2) �ڽ�(world)����

    //�߽��� �� ������Ʈ�� SRT�� �޾Ƽ� �ڿ� ���ϸ� �̵����� �ٲ�Եȴ�-> �¾��� SRT�� ����.
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