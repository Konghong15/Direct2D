#include "GameProcessor.h"

#include "RenderManger.h"
#include "TimeManger.h"
#include "InputManager.h"
#include "IBaseInterface.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "EventManager.h"

#include <cassert>

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
		EventManager::mInstance = new EventManager;
		ObjectManager::mInstance = new ObjectManager;
	}

	GameProcessor::~GameProcessor()
	{
		delete mTimeManager;
		delete mRenderManager;
		delete mSceneManager;
		delete InputManager::mInstance;
		InputManager::mInstance = nullptr;
		delete EventManager::mInstance;
		EventManager::mInstance = nullptr;
		delete ObjectManager::mInstance;
		ObjectManager::mInstance = nullptr;
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

		curScene.Update(DELTA_TIME);
		// lateUpdate?
		curScene.Render(mRenderManager);

		curScene.HandleSpawnObject();
		ObjectManager::mInstance->handleDeleteObject();

		EventManager::mInstance->handleEvent();
	}

	void GameProcessor::Destroy()
	{
		mRenderManager->Release();
		mSceneManager->Release();
		EventManager::mInstance->release();
		IBaseInterface::SetGameProcessor(nullptr);
		CoUninitialize();
	}
}