#include <cassert>

#include "TempComponent.h"
#include "InputManager.h"
#include "Transform.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include "BoxSprite.h"

namespace d2dDemo
{
	TempComponent::TempComponent(d2dFramework::GameObject* owner)
		: Component(owner)
	{
	}

	void TempComponent::Update(float deltaTime)
	{
		using namespace d2dFramework;
		Transform* transform = GetGameObject()->GetComponent<Transform>();
		assert(transform != nullptr);

		const float DELTA_MOVE = 1000 * deltaTime;

		if (InputManager::GetInstance()->GetKeyState('R') == eKeyState::Hold)
		{
			transform->AddRotate(deltaTime * 90);
		}
		else if (InputManager::GetInstance()->GetKeyState('T') == eKeyState::Hold)
		{
			transform->AddRotate(-deltaTime * 90);
		}

		BoxCollider* boxCollider = GetGameObject()->GetComponent<BoxCollider>();
		assert(boxCollider != nullptr);
		BoxSprite* boxSprite = GetGameObject()->GetComponent<BoxSprite>();
		assert(boxSprite != nullptr);

		if (boxCollider->GetColliderInfo().bIsCollision)
		{
			boxSprite->SetBaseColor({ 1,0,0,1 });
		}
		else
		{
			boxSprite->SetBaseColor({ 1,0,0, 0.5f });
		}
	}
}