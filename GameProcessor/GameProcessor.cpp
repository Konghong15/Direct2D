#include <cassert>

#include "GameProcessor.h"
#include "RenderManger.h"
#include "TimeManger.h"
#include "InputManager.h"

namespace gameProcessor
{
	GameProcessor::GameProcessor(UINT width, UINT height, std::wstring name)
		: mWidth(width)
		, mHeight(height)
		, mTitle(name)
		, mTimeManager(new TimeManager())
		, mRenderManager(new RenderManager())
		, mInputManager(new InputManager())
	{
	}

	GameProcessor::~GameProcessor()
	{
		delete mTimeManager;
		delete mRenderManager;
		delete mInputManager;
	}

	void GameProcessor::Init()
	{
		HRESULT hr;
		hr = CoInitialize(NULL);
		assert(SUCCEEDED(hr));

		mRenderManager->Init();
		mTimeManager->Init();
		mInputManager->Init();
	}

	void GameProcessor::Update()
	{
		mTimeManager->Update();
		mInputManager->Update();
	}

	void GameProcessor::Destroy()
	{
		mRenderManager->Release();
		CoUninitialize();
	}
}