#include "System.h"
#include "Entity.h"
#include "RenderManger.h"
#include "eComponentType.h"
#include "MovementComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "CamaraComponent.h"
#include "Helper.h"

namespace entityCamara
{
	void System::Update(std::vector<Entity*> entities, float deltaTime)
	{
		for (auto iter = entities.begin(); iter != entities.end(); ++iter)
		{
			Entity* entity = *iter;

			// 이 영역 나중에는 스위치 케이스로 빠르게 최적화 할 수 있을 거 같다.
			if (entity->CheckBitflag(2, eComponentType::Transform, eComponentType::Movement))
			{
				MovementComponent* movementComponent = static_cast<MovementComponent*>(entity->GetComponentOrNull(eComponentType::Movement));
				movementComponent->Update(deltaTime);

				TransformComponent* transformComponent = static_cast<TransformComponent*>(entity->GetComponentOrNull(eComponentType::Transform));
				transformComponent->AddTranslate(movementComponent->GetVelocity());
				transformComponent->Update();
			}
			else if (entity->CheckBitflag(1, eComponentType::Transform))
			{
				TransformComponent* transformComponent = static_cast<TransformComponent*>(entity->GetComponentOrNull(eComponentType::Transform));
				transformComponent->Update();
			}
			else if (entity->CheckBitflag(1, eComponentType::Movement))
			{
				MovementComponent* movementComponent = static_cast<MovementComponent*>(entity->GetComponentOrNull(eComponentType::Movement));
				movementComponent->Update(deltaTime);
			}
		}
	}

	void System::Render(std::vector<Entity*> entities, gameProcessor::RenderManager* renderManager)
	{
		renderManager->BeginDraw();

		for (auto iter = entities.begin(); iter != entities.end(); ++iter)
		{
			Entity* entity = *iter;

			unsigned long long checkFlag = 0;
			if (entity->CheckBitflag(3, eComponentType::Transform, eComponentType::Render, eComponentType::Camara))
			{
				TransformComponent* transformComponent = static_cast<TransformComponent*>(entity->GetComponentOrNull(eComponentType::Transform));
				RenderComponent* renderComponent = static_cast<RenderComponent*>(entity->GetComponentOrNull(eComponentType::Render));
				CamaraComponent* camaraComponent = static_cast<CamaraComponent*>(entity->GetComponentOrNull(eComponentType::Camara));

				renderComponent->Render(renderManager, transformComponent->GetTransform() * camaraComponent->GetInverseMatrix());
			}
			else if (entity->CheckBitflag(2, eComponentType::Transform, eComponentType::Render))
			{
				TransformComponent* transformComponent = static_cast<TransformComponent*>(entity->GetComponentOrNull(eComponentType::Transform));
				RenderComponent* renderComponent = static_cast<RenderComponent*>(entity->GetComponentOrNull(eComponentType::Render));

				renderComponent->Render(renderManager, transformComponent->GetTransform());
			}
			else if (entity->CheckBitflag(1, eComponentType::Render))
			{
				RenderComponent* renderComponent = static_cast<RenderComponent*>(entity->GetComponentOrNull(eComponentType::Render));
				renderComponent->Render(renderManager);
			}
		}

		renderManager->EndDraw();
	}
}