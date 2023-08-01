#pragma once

#include <vector>
#include <string>

namespace d2dFramework
{
	class ICollideable;
	class IFixedUpdateable;
	class IUpdateable;
	class IRenderable;
	class RenderManager;

	class Scene
	{
	public:
		Scene(const std::string& string);
		virtual ~Scene();

		// scene fsm Ã³¸®
		virtual void Enter() = 0;
		virtual void Exit() = 0;

		void FixedUpdate(float deltaTime);
		void Update(float deltaTime);
		void Render(RenderManager* renderManager);
		void HandleSpawnObject();

		inline void RegisterFixedUpdateable(IFixedUpdateable* fixedUpdateable);
		inline void RegisterUpdateable(IUpdateable* updateable);
		inline void RegisterRenderable(IRenderable* renderable);

		inline void UnregisterFixedUpdateable(IFixedUpdateable* fixedUpdateable);
		inline void UnregisterUpdateable(IUpdateable* updateable);
		inline void UnregisterRenderable(IRenderable* renderable);

	private:
		std::string mName;

		std::vector<IFixedUpdateable*> mFixedUpdateable;
		std::vector<IUpdateable*> mUpdateable;
		std::vector<IRenderable*> mRenderable;

		std::vector<IFixedUpdateable*> mCreateFixedUpdateable;
		std::vector<IUpdateable*> mCreateUpdateable;
		std::vector<IRenderable*> mCreateRenderable;
	};

	void Scene::RegisterFixedUpdateable(IFixedUpdateable* fixedUpdateable)
	{
		mCreateFixedUpdateable.push_back(fixedUpdateable);
	}
	void Scene::RegisterUpdateable(IUpdateable* updateable)
	{
		mCreateUpdateable.push_back(updateable);
	}
	void Scene::RegisterRenderable(IRenderable* renderable)
	{
		mCreateRenderable.push_back(renderable);
	}

	void Scene::UnregisterFixedUpdateable(IFixedUpdateable* fixedUpdateable)
	{
		mFixedUpdateable.erase(std::find(mFixedUpdateable.begin(), mFixedUpdateable.end(), fixedUpdateable));
	}
	void Scene::UnregisterUpdateable(IUpdateable* updateable)
	{
		mUpdateable.erase(std::find(mUpdateable.begin(), mUpdateable.end(), updateable));
	}
	void Scene::UnregisterRenderable(IRenderable* renderable)
	{
		mRenderable.erase(std::find(mRenderable.begin(), mRenderable.end(), renderable));
	}
}