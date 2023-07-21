#pragma once

#include <cassert>
#include <string>
#include <windows.h>

namespace gameProcessor
{
	class TimeManager;
	class RenderManager;
	class InputManager;

	class GameProcessor
	{
	public:
		GameProcessor(UINT width, UINT height, std::wstring name);
		virtual ~GameProcessor();

		virtual void Init() = 0; // default pure virtual function
		virtual void Update() = 0; // default pure virtual function
		virtual void Render() = 0;
		virtual void Destroy() = 0; // default pure virtual function

		inline UINT GetWidth() const;
		inline UINT GetHeight() const;
		inline const WCHAR* GetTitle() const;

		inline TimeManager* GetTimeManager() const;
		inline RenderManager* GetRenderManager() const;
		inline InputManager* GetInputManager() const;

	private:
		UINT mWidth;
		UINT mHeight;
		std::wstring mTitle;

		TimeManager* mTimeManager;
		RenderManager* mRenderManager;
		InputManager* mInputManager;
	};

	UINT GameProcessor::GetWidth() const
	{
		return mWidth;
	}

	UINT GameProcessor::GetHeight() const
	{
		return mHeight;
	}

	const WCHAR* GameProcessor::GetTitle() const
	{
		return mTitle.c_str();
	}

	TimeManager* GameProcessor::GetTimeManager() const
	{
		assert(mTimeManager != nullptr);
		return mTimeManager;
	}

	RenderManager* GameProcessor::GetRenderManager() const
	{
		assert(mRenderManager != nullptr);
		return mRenderManager;
	}

	InputManager* GameProcessor::GetInputManager() const
	{
		assert(mInputManager != nullptr);
		return mInputManager;
	}
}
