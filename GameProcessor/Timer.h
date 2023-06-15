#pragma once

#include <Windows.h>

namespace gameProcessor
{
	class Timer
	{
	public:
		Timer();
		~Timer() = default;
		
		void Init();
		void Update();

		inline float GetDeltaTime();
		inline unsigned int GetFPS();

	private:
		LARGE_INTEGER mCurTime;
		LARGE_INTEGER mPrevTime;
		LARGE_INTEGER mFrequency;
		unsigned int mFrameCount;
		unsigned int mFPS;

		float mDeltaTime;
	};

	float Timer::GetDeltaTime()
	{
		return  mDeltaTime > 0.03f ? 0.03f : mDeltaTime;
	}

	unsigned int Timer::GetFPS()
	{
		return mFPS;
	}
}