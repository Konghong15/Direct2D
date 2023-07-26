#include <cassert>

#include "PlayerComponent.h"
#include "InputManager.h"
#include "Transform.h"
#include "GameObject.h"

namespace d2dDemo
{
	PlayerComponent::PlayerComponent(d2dFramework::GameObject* owner)
		: Component(owner)
	{
	}

	void PlayerComponent::Update(float deltaTime)
	{
		using namespace d2dFramework;
		Transform* transform = GetGameObject()->GetComponent<Transform>();
		assert(transform != nullptr);

		const float DELTA_MOVE = 1000 * deltaTime;

		if (InputManager::GetInstance()->GetKeyState(VK_UP) == eKeyState::Hold)
		{
			transform->AddTranslate({ 0, -DELTA_MOVE });
		}
		else if (InputManager::GetInstance()->GetKeyState(VK_DOWN) == eKeyState::Hold)
		{
			transform->AddTranslate({ 0, DELTA_MOVE });
		}

		if (InputManager::GetInstance()->GetKeyState(VK_LEFT) == eKeyState::Hold)
		{
			transform->AddTranslate({ -DELTA_MOVE, 0 });
		}
		else if (InputManager::GetInstance()->GetKeyState(VK_RIGHT) == eKeyState::Hold)
		{
			transform->AddTranslate({ DELTA_MOVE, 0 });
		}
	}
}