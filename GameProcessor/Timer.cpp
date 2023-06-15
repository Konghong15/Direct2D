#include "Timer.h"

namespace gameProcessor
{
	Timer::Timer()
	{
		Init();
	}

	void Timer::Init()
	{
		QueryPerformanceFrequency(&mFrequency);
		QueryPerformanceCounter(&mCurTime);
		mPrevTime = mCurTime;
		mDeltaTime = 0.f;
		mFrameCount = 0;
		mFPS = 0;
	}

	void Timer::Update()
	{
		static float sTime = 0.f;
		sTime += GetDeltaTime();

		if (sTime >= 1.f)
		{
			sTime -= 1.f;
			mFPS = mFrameCount;
			mFrameCount = 0;
		}

		mDeltaTime = static_cast<float>(mCurTime.QuadPart - mPrevTime.QuadPart) / mFrequency.QuadPart;
		mPrevTime = mCurTime;
		QueryPerformanceCounter(&mCurTime);
		++mFrameCount;
	}
}