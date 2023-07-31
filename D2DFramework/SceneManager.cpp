#include "SceneManager.h"

#include "EventManager.h"
#include "Scene.h"

namespace d2dFramework
{
	SceneManager::SceneManager()
		: mCurrentScene(nullptr)
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
		EventManager::GetInstance()->RegisterEventHandler(key, changeScene);
	}

	void SceneManager::Release()
	{
		for (auto iter = mSceneMap.begin(); iter != mSceneMap.end(); ++iter)
		{
			Scene* scene = iter->second;
			scene->Exit();
		}
	}
}