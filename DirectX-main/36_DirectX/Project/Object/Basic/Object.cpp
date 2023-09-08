#include "Framework.h"
#include "Object.h"



Object::Object(XMFLOAT4 color)
{
    XMFLOAT3 pos  = {   0.0f,   0.0f, 0.0f };
    XMFLOAT3 size = { 100.0f, 100.0f, 0.0f };

    float L = pos.x - size.x * 0.5f;
    float R = pos.x + size.x * 0.5f;
    float B = pos.y - size.y * 0.5f;
    float T = pos.y + size.y * 0.5f;

    //Vertex Buffer
    vertices = {
        {XMFLOAT3(L,T,0.0f), color},//LT
        {XMFLOAT3(R,T,0.0f), color},//RT
        {XMFLOAT3(L,B,0.0f), color},//LB
        {XMFLOAT3(R,B,0.0f), color},//RB

        //BackFace Culling: 뒷면을 그리지 않는다-시계방향으로 그리면 화면방향으로 앞면이고 반시계로 그려지면 화면방향이 뒷면이다.

        //Polygon: 다각형, directx는 삼각형을 이어붙여서 도형을 만든다.
    };

    indices = {
        0, 1, 2,
        2, 1, 3,
    };


    vertexBuffer = new VertexBuffer(vertices);
    indexBuffer  = new  IndexBuffer(indices);

    vertexShader = new VertexShader(L"VertexTutorial");
    pixelShader  = new  PixelShader(L"PixelTutorial");


    ////ViewPort
}



Object::~Object()
{
    delete vertexShader;
    delete vertexBuffer;
    delete  pixelShader;
    delete  indexBuffer;
}

void Object::Render()
{
    vertexBuffer->SetBuffer();
     indexBuffer->SetBuffer();
    vertexShader->SetShader();
     pixelShader->SetShader();

    //Render - draw함수로 파이프라인을 작동시킨다.
    //DC->Draw(vertices.size(), 0);
    DC->DrawIndexed(indices.size(), 0, 0);
    ////////////////////////////////////////////
}
