#pragma once

#include <cassert>
#include <string>
#include <map>

namespace d2dFramework
{
	class Scene;

	class SceneManager final
	{
	public:
		SceneManager();
		~SceneManager();
		SceneManager(const SceneManager&) = delete;
		SceneManager& operator=(const SceneManager&) = delete;

		inline Scene& GetCurrentScene() const;
		inline void RegisterScene(const std::string& sceneName, Scene* scene);

	private:
		Scene* mCurrentScene;
		std::map<std::string, Scene*> mSceneMap;
	};

	Scene& SceneManager::GetCurrentScene() const
	{
		assert(mCurrentScene != nullptr);
		return *mCurrentScene;
	}

	void SceneManager::RegisterScene(const std::string& sceneName, Scene* scene)
	{
		if (mCurrentScene == nullptr)
		{
			mCurrentScene = scene;
		}

		auto iter = mSceneMap.find(sceneName);
		assert(iter == mSceneMap.end()); // 동일한 이름의 씬을 등록하면 안댐

		mSceneMap.insert({ sceneName, scene });
	}
}