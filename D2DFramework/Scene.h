#pragma once

#include <string>
#include <vector>

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

		// scene fsm 처리
		virtual void Enter() = 0;
		virtual void Exit() = 0;

		void HandleCollision();
		void FixedUpdate(float deltaTime);
		void Update(float deltaTime);
		void Render(RenderManager* renderManager);
		void HandleObjectReference(); // create, delete handling 

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

		std::vector<ICollideable*> mCreateCollideable;
		std::vector<IFixedUpdateable*> mCreateFixedUpdateable;
		std::vector<IUpdateable*> mCreateUpdateable;
		std::vector<IRenderable*> mCreateRenderable;

		// 지연 소멸되는 개체는 실제로는 댕글링 포인터로 참조를 지우는 역할만을 수행해야 한다.
		std::vector<ICollideable*> mDeleteCollideable;
		std::vector<IFixedUpdateable*> mDeleteFixedUpdateable;
		std::vector<IUpdateable*> mDeleteUpdateable;
		std::vector<IRenderable*> mDeleteRenderable;
	};

	void Scene::RegisterCollideable(ICollideable* collideable)
	{
		mCreateCollideable.push_back(collideable);
	}
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

	void Scene::UnregisterCollideable(ICollideable* collideable)
	{
		mDeleteCollideable.push_back(collideable);
	}
	void Scene::UnregisterFixedUpdateable(IFixedUpdateable* fixedUpdateable)
	{
		mDeleteFixedUpdateable.push_back(fixedUpdateable);
	}
	void Scene::UnregisterUpdateable(IUpdateable* updateable)
	{
		mDeleteUpdateable.push_back(updateable);
	}
	void Scene::UnregisterRenderable(IRenderable* renderable)
	{
		mDeleteRenderable.push_back(renderable);
	}
}