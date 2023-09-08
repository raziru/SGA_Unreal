#include "Framework.h"
#include "Time.h"


float Time::timeElapsed = 0.0f;


Time::Time()
{

	QueryPerformanceFrequency((LARGE_INTEGER*)&ticksPerSecond); // cpu�� �ʴ� ������

	QueryPerformanceCounter((LARGE_INTEGER*)&lastTick);// cpu�� ����(tick) ���� ��

}

Time::~Time()
{
}

void Time::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&curTick);//���� cpu�� ����(tick) ���� ��

	timeElapsed = (float)(curTick - lastTick) / (float)ticksPerSecond;

	runningTime += timeElapsed;

	oneSecCount += timeElapsed;

	if (oneSecCount >= 1.0f)
	{
		frameRate = frameCount;
		frameCount = 0;

		oneSecCount -= 1.0f;

	}

	frameCount++;
	lastTick = curTick;
}

