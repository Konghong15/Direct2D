#pragma once

#include "BaseEntity.h"

#include <cassert>
#include <string>
#include <map>

namespace d2dFramework
{
	class Scene;
	class IFixedUpdateable;
	class IUpdateable;

	class SceneManager final : public BaseEntity
	{
	public:
		SceneManager();
		~SceneManager();
		SceneManager(const SceneManager&) = delete;
		SceneManager& operator=(const SceneManager&) = delete;

		void Init();
		void FixedUpdate(float deltaTime);
		void Update(float deltaTime);
		void Release();

		inline void RegisterScene(const std::string& sceneName, Scene* scene);
		inline void RegisterFixedUpdateable(IFixedUpdateable* fixedUpdateable);
		inline void RegisterUpdateable(IUpdateable* updateable);

		inline void UnregisterFixedUpdateable(IFixedUpdateable* fixedUpdateable);
		inline void UnregisterUpdateable(IUpdateable* updateable);

		inline Scene& GetCurrentScene() const;

	private:
		Scene* mCurrentScene;
		std::map<std::string, Scene*> mSceneMap;

		std::vector<IFixedUpdateable*> mFixedUpdateable;
		std::vector<IUpdateable*> mUpdateable;
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
	void SceneManager::RegisterFixedUpdateable(IFixedUpdateable* fixedUpdateable)
	{
		mFixedUpdateable.push_back(fixedUpdateable);
	}
	void SceneManager::RegisterUpdateable(IUpdateable* updateable)
	{
		mUpdateable.push_back(updateable);
	}

	void SceneManager::UnregisterFixedUpdateable(IFixedUpdateable* fixedUpdateable)
	{
		mFixedUpdateable.erase(std::find(mFixedUpdateable.begin(), mFixedUpdateable.end(), fixedUpdateable));
	}
	void SceneManager::UnregisterUpdateable(IUpdateable* updateable)
	{
		mUpdateable.erase(std::find(mUpdateable.begin(), mUpdateable.end(), updateable));
	}

	Scene& SceneManager::GetCurrentScene() const
	{
		return *mCurrentScene;
	}
}