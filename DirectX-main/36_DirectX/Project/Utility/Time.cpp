#include "Framework.h"
#include "Time.h"


float Time::timeElapsed = 0.0f;


Time::Time()
{

	QueryPerformanceFrequency((LARGE_INTEGER*)&ticksPerSecond); // cpu의 초당 진동수

	QueryPerformanceCounter((LARGE_INTEGER*)&lastTick);// cpu의 진동(tick) 누적 값

}

Time::~Time()
{
}

void Time::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&curTick);//현재 cpu의 진동(tick) 누적 값

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

