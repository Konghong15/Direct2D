#include "D2DEntityCamara.h"
#include "EntityManager.h"
#include "Entity.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "MovementComponent.h"
#include "CamaraComponent.h"

namespace entityCamara
{
	D2DEntityCamara::D2DEntityCamara(UINT width, UINT height, std::wstring name)
		: GameProcessor(width, height, name)
		, mEntityManager(nullptr)
		, mSystem()
	{
	}

	void D2DEntityCamara::Init()
	{
		mEntityManager = new EntityManager();
		mTimeManager.Init();
		mRenderManager.Init();

		int id = 0;
		RenderComponent* renderComponent;
		TransformComponent* transformComponent;
		CamaraComponent* camaraComponent;

		Entity* entity = mEntityManager->CreateEntity(id++);
		renderComponent = new RenderComponent(entity->GetEntityId(), { -100, -100, 100, 100 });
		transformComponent = new TransformComponent(entity->GetEntityId(), { 1.f, 1.f }, 0.f, { 0.f, 0.f });
		camaraComponent = new CamaraComponent(entity->GetEntityId(), { 0, 0, static_cast<float>(GetWidth()), static_cast<float>(GetHeight()) }, { 1.f, -1.f }, 0.f, { -static_cast<float>(GetWidth()) / 2, static_cast<float>(GetHeight()) / 2 });
		 
		entity->AddComponent(renderComponent);
		entity->AddComponent(transformComponent);
		entity->AddComponent(camaraComponent);

		// load entity data

		// register callback
	}

	void D2DEntityCamara::Update()
	{
		// manager update
		mTimeManager.Update();

		// system update
		mSystem.Update(mEntityManager->GetEntity());
	}

	void D2DEntityCamara::Render()
	{
	}

	void D2DEntityCamara::Destroy()
	{
		mRenderManager.Release();

		delete mEntityManager;
		mEntityManager = nullptr;
	}
}