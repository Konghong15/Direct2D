#pragma once

#include <string>
#include <vector>

namespace d2dFramework
{
	class ICollideable;
	class IFixedUpdateable;
	class IUpdateable;
	class IRenderable;

	class Scene
	{
	public:
		Scene(const std::string& string);
		virtual ~Scene();

		// scene fsm Ã³¸®
		virtual void Enter() = 0;
		virtual void Exit() = 0;

		void HandleCollision();
		void FixedUpdate(float deltaTime);
		void Update(float deltaTime);
		void Render();

		inline void RegisterCollideable(ICollideable* collideable);
		inline void RegisterFixedUpdateable(IFixedUpdateable* fixedUpdateable);
		inline void RegisterUpdateable(IUpdateable* updateable);
		inline void RegisterRenderable(IRenderable* renderable);

		inline void UnregisterCollideable(ICollideable* collideable);
		inline void UnregisterFixedUpdateable(IFixedUpdateable* fixedUpdateable);
		inline void UnregisterUpdateable(IUpdateable* updateable);
		inline void UnregisterRenderable(IRenderable* renderable);

	private:
		std::string mName;

		std::vector<ICollideable*> mCollideable;
		std::vector<IFixedUpdateable*> mFixedUpdateable;
		std::vector<IUpdateable*> mUpdateable;
		std::vector<IRenderable*> mRenderable;
	};

	void Scene::RegisterCollideable(ICollideable* collideable)
	{
		mCollideable.push_back(collideable);
	}
	void Scene::RegisterFixedUpdateable(IFixedUpdateable* fixedUpdateable)
	{
		mFixedUpdateable.push_back(fixedUpdateable);
	}
	void Scene::RegisterUpdateable(IUpdateable* updateable)
	{
		mUpdateable.push_back(updateable);
	}
	void Scene::RegisterRenderable(IRenderable* renderable)
	{
		mRenderable.push_back(renderable);
	}

	void Scene::UnregisterCollideable(ICollideable* collideable)
	{
		auto iter = std::find(mCollideable.begin(), mCollideable.end(), collideable);

		if (iter != mCollideable.end())
		{
			mCollideable.erase(iter);
		}
	}
	void Scene::UnregisterFixedUpdateable(IFixedUpdateable* fixedUpdateable)
	{
		auto iter = std::find(mFixedUpdateable.begin(), mFixedUpdateable.end(), fixedUpdateable);

		if (iter != mFixedUpdateable.end())
		{
			mFixedUpdateable.erase(iter);
		}
	}
	void Scene::UnregisterUpdateable(IUpdateable* updateable)
	{
		auto iter = std::find(mUpdateable.begin(), mUpdateable.end(), updateable);

		if (iter != mUpdateable.end())
		{
			mUpdateable.erase(iter);
		}
	}
	void Scene::UnregisterRenderable(IRenderable* renderable)
	{
		auto iter = std::find(mRenderable.begin(), mRenderable.end(), renderable);

		if (iter != mRenderable.end())
		{
			mRenderable.erase(iter);
		}
	}
}