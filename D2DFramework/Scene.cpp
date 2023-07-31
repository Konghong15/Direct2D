#include "Scene.h"

#include "GameObject.h"
#include "ICollideable.h"
#include "IFixedUpdateable.h"
#include "IUpdateable.h"
#include "IRenderable.h"
#include "RenderManger.h"

#include <cassert>

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

	void Scene::HandleCollision()
	{
		for (size_t i = 0; i < mCollideable.size(); ++i)
		{
			mCollideable[i]->UpdateCollider();
		}

		for (size_t i = 0; i < mCollideable.size(); ++i)
		{
			for (size_t j = i + 1; j < mCollideable.size(); ++j)
			{
				mCollideable[i]->HandleCollision(mCollideable[j]);
			}
		}
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

	void Scene::HandleObjectReference()
	{
		mCollideable.insert(mCollideable.end(), mCreateCollideable.begin(), mCreateCollideable.end());
		mFixedUpdateable.insert(mFixedUpdateable.end(), mCreateFixedUpdateable.begin(), mCreateFixedUpdateable.end());
		mUpdateable.insert(mUpdateable.end(), mCreateUpdateable.begin(), mCreateUpdateable.end());
		mRenderable.insert(mRenderable.end(), mCreateRenderable.begin(), mCreateRenderable.end());

		for (auto iter = mDeleteCollideable.begin(); iter != mDeleteCollideable.end(); ++iter)
		{
			mCollideable.erase(std::find(mCollideable.begin(), mCollideable.end(), *iter));
		}
		for (auto iter = mDeleteFixedUpdateable.begin(); iter != mDeleteFixedUpdateable.end(); ++iter)
		{
			mFixedUpdateable.erase(std::find(mFixedUpdateable.begin(), mFixedUpdateable.end(), *iter));
		}
		for (auto iter = mDeleteUpdateable.begin(); iter != mDeleteUpdateable.end(); ++iter)
		{
			mUpdateable.erase(std::find(mUpdateable.begin(), mUpdateable.end(), *iter));
		}
		for (auto iter = mDeleteRenderable.begin(); iter != mDeleteRenderable.end(); ++iter)
		{
			mRenderable.erase(std::find(mRenderable.begin(), mRenderable.end(), *iter));
		}

		mCreateCollideable.clear();
		mCreateFixedUpdateable.clear();
		mCreateUpdateable.clear();
		mCreateRenderable.clear();

		mDeleteCollideable.clear();
		mDeleteFixedUpdateable.clear();
		mDeleteUpdateable.clear();
		mDeleteRenderable.clear();
	}
}