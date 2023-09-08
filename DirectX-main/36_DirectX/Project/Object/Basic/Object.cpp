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

        //BackFace Culling: �޸��� �׸��� �ʴ´�-�ð�������� �׸��� ȭ��������� �ո��̰� �ݽð�� �׷����� ȭ������� �޸��̴�.

        //Polygon: �ٰ���, directx�� �ﰢ���� �̾�ٿ��� ������ �����.
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

    //Render - draw�Լ��� ������������ �۵���Ų��.
    //DC->Draw(vertices.size(), 0);
    DC->DrawIndexed(indices.size(), 0, 0);
    ////////////////////////////////////////////
}
