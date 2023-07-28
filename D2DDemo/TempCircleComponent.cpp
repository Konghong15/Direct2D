#include <cassert>

#include "TempCircleComponent.h"
#include "InputManager.h"
#include "Transform.h"
#include "GameObject.h"
#include "CircleCollider.h"
#include "CircleSprite.h"

namespace d2dDemo
{
	TempCircleComponent::TempCircleComponent(d2dFramework::GameObject* owner)
		: Component(owner)
	{
	}

	void TempCircleComponent::Update(float deltaTime)
	{
		using namespace d2dFramework;
		Transform* transform = GetGameObject()->GetComponent<Transform>();
		assert(transform != nullptr);

		if (InputManager::GetInstance()->GetKeyState('R') == eKeyState::Hold)
		{
			transform->AddRotate(deltaTime * 90);
		}
		else if (InputManager::GetInstance()->GetKeyState('T') == eKeyState::Hold)
		{
			transform->AddRotate(-deltaTime * 90);
		}

		CircleCollider* circleCollider = GetGameObject()->GetComponent<CircleCollider>();
		assert(circleCollider != nullptr);
		CircleSprite* circleSprite = GetGameObject()->GetComponent<CircleSprite>();
		assert(circleSprite != nullptr);

		if (circleCollider->GetColliderInfo().bIsCollision)
		{
			circleSprite->SetBaseColor({ 1,0,0,1 });
		}
		else
		{
			circleSprite->SetBaseColor({ 1,0,0, 0.5f });
		}
	}
}