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
		camaraComponent = new CamaraComponent(entity->GetEntityId(), { 0, 0, static_cast<float>(mWidth), static_cast<float>(mHeight) }, { 1.f, -1.f }, 0.f, { -static_cast<float>(mWidth) / 2, static_cast<float>(mHeight) / 2 });

		entity->AddComponent(renderComponent);
		entity->AddComponent(transformComponent);
		entity->AddComponent(camaraComponent);
	}

	void D2DEntityCamara::Update()
	{
		mTimeManager.Update();
		const float DELTA_TIME = mTimeManager.GetDeltaTime();

		mSystem.Update(mEntityManager->GetEntity(), DELTA_TIME);
	}

	void D2DEntityCamara::Render()
	{
		mSystem.Render(mEntityManager->GetEntity(), &mRenderManager);
	}

	void D2DEntityCamara::Destroy()
	{
		mRenderManager.Release();

		delete mEntityManager;
		mEntityManager = nullptr;
	}
}