#include <cassert>

#include "GameProcessor.h"
#include "RenderManger.h"
#include "TimeManger.h"
#include "InputManager.h"

#include "IBaseInterface.h"
#include "ICollideable.h"
#include "IFixedUpdateable.h"
#include "IUpdateable.h"
#include "IRenderable.h"

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

		mRenderManager->Init();
		mTimeManager->Init();
		InputManager::mInstance->Init();

		IBaseInterface::SetGameProcessor(this);
	}

	void GameProcessor::Update()
	{
		mTimeManager->Update();
		InputManager::mInstance->Update();

		{
			const float DELTA_TIME = mTimeManager->GetDeltaTime();
			assert(DELTA_TIME >= 0.f);

			collision();
			fixedUpdate(DELTA_TIME);
			update(DELTA_TIME);
			render();
		}
	}

	void GameProcessor::Destroy()
	{
		mRenderManager->Release();
		CoUninitialize();
		IBaseInterface::SetGameProcessor(nullptr);
	}

	void GameProcessor::collision()
	{
		for (size_t i = 0; i < mCollideable.size(); ++i)
		{
			for (size_t j = i + 1; j < mCollideable.size(); ++j)
			{
				mCollideable[i]->HandleCollision(mCollideable[j]);
			}
		}
	}

	void GameProcessor::fixedUpdate(float deltaTime)
	{
		for (IFixedUpdateable* fixedUpdateable : mFixedUpdateable)
		{
			fixedUpdateable->FixedUpdate(deltaTime);
		}
	}

	void GameProcessor::update(float deltaTime)
	{
		for (IUpdateable* updateable : mUpdateable)
		{
			updateable->Update(deltaTime);
		}
	}

	void GameProcessor::render()
	{
		assert(mRenderManager != nullptr);

		mRenderManager->BeginDraw();

		for (IRenderable* renderable : mRenderable)
		{
			renderable->Render(mRenderManager);
		}

		mRenderManager->EndDraw();
	}
}