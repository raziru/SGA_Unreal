#include "Framework.h"
#include "Environment.h"


Environment::Environment()
{
    viewMatrix = XMMatrixIdentity();

    projectionMatrix = XMMatrixOrthographicOffCenterLH
    (
        0.0f, WIN_WIDTH,  //X��
        0.0f, WIN_HEIGHT, //Y��
        0.0f, 1.0f        //Z�� - near frame(z), far frame(z) ȭ�� z�� �ѵ�
        // ������ ������ �׸��� �ʴ´�.
    );
    //orthographic:, offcenter: ���� �Ʒ��� (0,0) lefthand: �޼���ǥ�� ->�ð�������� �׷��� ǥ��

	      viewBuffer = new MatrixBuffer();
	projectionBuffer = new MatrixBuffer();
}

Environment::~Environment()
{
    delete       viewBuffer;
    delete projectionBuffer;
}

void Environment::Update()
{
}

void Environment::Set()
{
          viewBuffer->SetData(      viewMatrix);
    projectionBuffer->SetData(projectionMatrix);

          viewBuffer->VSSetBuffer(1);
    projectionBuffer->VSSetBuffer(2);
}


