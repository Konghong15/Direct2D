#include <cassert>

#include "GameProcessor.h"
#include "RenderManger.h"
#include "TimeManger.h"
#include "InputManager.h"

#include "Scene.h"
#include "SceneManager.h"
#include "IBaseInterface.h"

namespace d2dFramework
{
	GameProcessor::GameProcessor(UINT width, UINT height, std::wstring name)
		: mWidth(width)
		, mHeight(height)
		, mTitle(name)
		, mTimeManager(new TimeManager())
		, mRenderManager(new RenderManager())
		, mSceneManager(new SceneManager())
	{
		InputManager::mInstance = new InputManager;
	}

	GameProcessor::~GameProcessor()
	{
		delete mTimeManager;
		delete mRenderManager;
		delete InputManager::mInstance;
		InputManager::mInstance = nullptr;
		delete mSceneManager;
	}

	void GameProcessor::Init()
	{
		HRESULT hr;
		hr = CoInitialize(NULL);
		assert(SUCCEEDED(hr));

		mRenderManager->Init();
		mTimeManager->Init();
		mSceneManager->Init();
		InputManager::mInstance->Init();

		IBaseInterface::SetGameProcessor(this);
	}

	void GameProcessor::Update()
	{
		static float s_FixedTime = 0.f;

		mTimeManager->Update();
		InputManager::mInstance->Update();

		const float DELTA_TIME = mTimeManager->GetDeltaTime();
		assert(DELTA_TIME >= 0.f);

		s_FixedTime += DELTA_TIME;

		Scene& curScene = mSceneManager->GetCurrentScene();
		while (s_FixedTime >= 0.02f)
		{
			curScene.FixedUpdate(0.02f);
			curScene.HandleCollision();

			s_FixedTime -= 0.02f;
		}

		update(DELTA_TIME);
		// lateUpdate()
		render();
		// handleEvent()
	}

	void GameProcessor::Destroy()
	{
		mRenderManager->Release();
		mSceneManager->Delete();
		CoUninitialize();
		IBaseInterface::SetGameProcessor(nullptr);
	}

	void GameProcessor::collision()
	{
		for (size_t i = 0; i < mCollideable.size(); ++i)
		{
			mCollideable[i]->UpdateCollider();
		}

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