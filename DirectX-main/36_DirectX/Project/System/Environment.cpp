#include "Framework.h"
#include "Environment.h"


Environment::Environment()
{
    viewMatrix = XMMatrixIdentity();

    projectionMatrix = XMMatrixOrthographicOffCenterLH
    (
        0.0f, WIN_WIDTH,  //X축
        0.0f, WIN_HEIGHT, //Y축
        0.0f, 1.0f        //Z축 - near frame(z), far frame(z) 화면 z축 한도
        // 범위를 넘으면 그리지 않는다.
    );
    //orthographic:, offcenter: 왼쪽 아래가 (0,0) lefthand: 왼손좌표계 ->시계방향으로 그려야 표현

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


