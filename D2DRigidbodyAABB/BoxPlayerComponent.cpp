#include "BoxPlayerComponent.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "InputManager.h"

namespace d2dRigidbodyAABB
{
	BoxPlayerComponent::BoxPlayerComponent(unsigned int id, d2dFramework::GameObject* owner)
		: Component(id, owner)
	{
	}

	void BoxPlayerComponent::Init()
	{
		IUpdateable::Init();
	}

	void BoxPlayerComponent::Update(float deltaTime)
	{
		using namespace d2dFramework;

		Rigidbody* rigidbody = GetGameObject()->GetComponent<Rigidbody>();

		if (InputManager::GetInstance()->GetKeyState(VK_UP) == eKeyState::Hold)
		{
			rigidbody->AddVelocity({ 0, mSpeed.GetY() * deltaTime });
		}
		else if (InputManager::GetInstance()->GetKeyState(VK_DOWN) == eKeyState::Hold)
		{
			rigidbody->AddVelocity({ 0, -mSpeed.GetY() * deltaTime });
		}

		if (InputManager::GetInstance()->GetKeyState(VK_LEFT) == eKeyState::Hold)
		{
			rigidbody->AddVelocity({ -mSpeed.GetX() * deltaTime , 0 });
		}
		else if (InputManager::GetInstance()->GetKeyState(VK_RIGHT) == eKeyState::Hold)
		{
			rigidbody->AddVelocity({ mSpeed.GetX() * deltaTime , 0 });
		}
	}

	void BoxPlayerComponent::Release()
	{
		IUpdateable::Release();
	}
}