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

		void Init();
		void Release();

		inline void RegisterScene(const std::string& sceneName, Scene* scene);
		inline Scene& GetCurrentScene() const;

	private:
		Scene* mCurrentScene;
		std::map<std::string, Scene*> mSceneMap;
	};

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

	Scene& SceneManager::GetCurrentScene() const
	{
		return *mCurrentScene;
	}
}