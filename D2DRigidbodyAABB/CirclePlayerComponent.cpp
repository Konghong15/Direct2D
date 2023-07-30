#include "CirclePlayerComponent.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "InputManager.h"

namespace d2dRigidbodyAABB
{
	CirclePlayerComponent::CirclePlayerComponent(d2dFramework::GameObject* owner)
		: Component(owner)
	{
	}

	void CirclePlayerComponent::Update(float deltaTime)
	{
		using namespace d2dFramework;

		Rigidbody* rigidbody = GetGameObject()->GetComponent<Rigidbody>();

		if (InputManager::GetInstance()->GetKeyState('W') == eKeyState::Hold)
		{
			rigidbody->AddVelocity({ 0, -mSpeed.GetY() * deltaTime });
		}
		else if (InputManager::GetInstance()->GetKeyState('S') == eKeyState::Hold)
		{
			rigidbody->AddVelocity({ 0, mSpeed.GetY() * deltaTime });
		}

		if (InputManager::GetInstance()->GetKeyState('A') == eKeyState::Hold)
		{
			rigidbody->AddVelocity({ -mSpeed.GetX() * deltaTime , 0 });
		}
		else if (InputManager::GetInstance()->GetKeyState('D') == eKeyState::Hold)
		{
			rigidbody->AddVelocity({ mSpeed.GetX() * deltaTime , 0 });
		}
	}
}