#include <cassert>

#include "GameProcessor.h"
#include "RenderManger.h"
#include "TimeManger.h"
#include "InputManager.h"

namespace d2dFramework
{
	GameProcessor::GameProcessor(UINT width, UINT height, std::wstring name)
		: mWidth(width)
		, mHeight(height)
		, mTitle(name)
		, mTimeManager(new TimeManager())
		, mRenderManager(new RenderManager())
	{
		InputManager::mInstance = new InputManager;
	}

	GameProcessor::~GameProcessor()
	{
		delete mTimeManager;
		delete mRenderManager;
		delete InputManager::mInstance;
		InputManager::mInstance = nullptr;
	}

	void GameProcessor::Init()
	{
		HRESULT hr;
		hr = CoInitialize(NULL);
		assert(SUCCEEDED(hr));

		// manager Init call
		mRenderManager->Init();
		mTimeManager->Init();
		InputManager::mInstance->Init();

		// interface Class Manager setting
	}

	void GameProcessor::Update()
	{
		mTimeManager->Update();
		InputManager::mInstance->Update();
		// float deltaTime;
		// gameManager->FixedUpdate(deltaTime);
		// gameManager->collisionManager->Check collision
		// gameManager->Update(deltaTime)
		// gmaeManager->Render(mRenderManager)
		// Event handle
	}

	void GameProcessor::Destroy()
	{
		mRenderManager->Release();
		CoUninitialize();
	}
}