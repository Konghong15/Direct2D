#include "SceneManager.h"

#include "IFixedUpdateable.h"
#include "IUpdateable.h"
#include "eFrameworkID.h"
#include "EventManager.h"
#include "Scene.h"

namespace d2dFramework
{
	SceneManager::SceneManager()
		: BaseEntity(static_cast<unsigned int>(eFramworkID::SceneManager))
		, mCurrentScene(nullptr)
	{
	}

	SceneManager::~SceneManager()
	{
		for (auto iter = mSceneMap.begin(); iter != mSceneMap.end(); ++iter)
		{
			Scene* scene = iter->second;
			delete scene;
		}

		mSceneMap.clear();
	}

	void SceneManager::Init()
	{
		mCurrentScene->Enter();

		const std::string& key = EventManager::GetInstance()->GetEventName(eDefaultEvent::ChangeScene);
		auto changeScene = [this](const std::string& data) -> void
		{
			auto nextScene = mSceneMap.find(data);
			if (nextScene == mSceneMap.end())
			{
				return;
			}

			mCurrentScene->Exit();
			mCurrentScene = nextScene->second;
			mCurrentScene->Enter();
		};

		EventManager::GetInstance()->RegisterEventHandler(key, BaseEntity::GetId(), changeScene);
	}

	void SceneManager::FixedUpdate(float deltaTime)
	{
		for (IFixedUpdateable* fixedUpdateable : mFixedUpdateable)
		{
			fixedUpdateable->FixedUpdate(deltaTime);
		}
	}

	void SceneManager::Update(float deltaTime)
	{
		for (IUpdateable* updateable : mUpdateable)
		{
			updateable->Update(deltaTime);
		}
	}

	void SceneManager::Release()
	{
		const std::string& key = EventManager::GetInstance()->GetEventName(eDefaultEvent::ChangeScene);
		EventManager::GetInstance()->UnRegisterEventHandler(key, BaseEntity::GetId()); 

		for (auto iter = mSceneMap.begin(); iter != mSceneMap.end(); ++iter)
		{
			Scene* scene = iter->second;
			scene->Exit();
		}
	}
}