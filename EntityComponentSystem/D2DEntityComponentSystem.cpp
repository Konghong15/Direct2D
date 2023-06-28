#include "D2DEntityComponentSystem.h"
#include "EntityManager.h"
#include "Entity.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "MovementComponent.h"

namespace entityComponentSystem
{
	D2DEntityComponentSystem::D2DEntityComponentSystem(UINT width, UINT height, std::wstring name)
		: GameProcessor(width, height, name)
		, mEntityManager(nullptr)
		, mSystem()
	{
	}

	void D2DEntityComponentSystem::Init()
	{
		mEntityManager = new EntityManager();
		mTimeManager.Init();
		mRenderManager.Init();

		int id = 0;
		RenderComponent* renderComponent;
		MovementComponent* movementComponent;
		TransformComponent* transformComponent;

		Entity* entity = mEntityManager->CreateEntity(id++);
		renderComponent = new RenderComponent(entity->GetEntityId(), { -100, -100, 100, 100 });
		transformComponent = new TransformComponent(entity->GetEntityId(), { 1.f, 1.f }, 0.f, { 800.f,600.f });

		entity->AddComponent(renderComponent);
		entity->AddComponent(transformComponent);
	}

	void D2DEntityComponentSystem::Update()
	{
		mTimeManager.Update();
		const float DELTA_TIME = mTimeManager.GetDeltaTime();

		mSystem.Update(mEntityManager->GetEntity(), DELTA_TIME);
	}

	void D2DEntityComponentSystem::Render()
	{
		mSystem.Render(mEntityManager->GetEntity(), &mRenderManager);
	}

	void D2DEntityComponentSystem::Destroy()
	{
		mRenderManager.Release();

		delete mEntityManager;
		mEntityManager = nullptr;
	}
}