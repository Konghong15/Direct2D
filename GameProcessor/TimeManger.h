#pragma once

#include <Windows.h>

namespace gameProcessor
{
	class TimeManager
	{
	public:
		TimeManager();
		~TimeManager() = default;
		
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

	float TimeManager::GetDeltaTime()
	{
		return  mDeltaTime > 0.03f ? 0.03f : mDeltaTime;
	}

	unsigned int TimeManager::GetFPS()
	{
		return mFPS;
	}
}