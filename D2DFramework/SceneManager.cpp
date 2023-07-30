#include "SceneManager.h"

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
}