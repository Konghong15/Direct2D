#include "Scene.h" // Çì´õ ÀÎ

#include "GameObject.h"
#include "ICollideable.h"
#include "IFixedUpdateable.h"
#include "IUpdateable.h"
#include "IRenderable.h"
#include "RenderManger.h"


namespace d2dFramework
{
	Scene::Scene(const std::string& name)
		: mName(name)
	{
	}

	Scene::~Scene()
	{
		mCollideable.clear();
		mFixedUpdateable.clear();
		mUpdateable.clear();
		mRenderable.clear();
	}

	void Scene::FixedUpdate(float deltaTime)
	{
		for (IFixedUpdateable* fixedUpdateable : mFixedUpdateable)
		{
			fixedUpdateable->FixedUpdate(deltaTime);
		}
	}

	void Scene::Update(float deltaTime)
	{
		for (IUpdateable* updateable : mUpdateable)
		{
			updateable->Update(deltaTime);
		}
	}

	void Scene::Render(RenderManager* renderManager)
	{
		assert(renderManager != nullptr);

		renderManager->BeginDraw();

		for (IRenderable* renderable : mRenderable)
		{
			renderable->Render(renderManager);
		}

		renderManager->EndDraw();
	}

	void Scene::HandleSpawnObject()
	{
		mCollideable.insert(mCollideable.end(), mCreateCollideable.begin(), mCreateCollideable.end());
		mFixedUpdateable.insert(mFixedUpdateable.end(), mCreateFixedUpdateable.begin(), mCreateFixedUpdateable.end());
		mUpdateable.insert(mUpdateable.end(), mCreateUpdateable.begin(), mCreateUpdateable.end());
		mRenderable.insert(mRenderable.end(), mCreateRenderable.begin(), mCreateRenderable.end());

		mCreateCollideable.clear();
		mCreateFixedUpdateable.clear();
		mCreateUpdateable.clear();
		mCreateRenderable.clear();
	}
}