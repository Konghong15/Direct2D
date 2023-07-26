#include <cassert>

#include "Movement.h"
#include "GameObject.h"
#include "Transform.h"

namespace d2dFramework
{
	Movement::Movement(GameObject* onwer)
		: Component(onwer)
		, mVelocity(0.f, 0.f)
		, mDirection(0.f, 0.f)
		, mSpeed(0.f)
	{
	}

	void Movement::Update(float deltaTime)
	{
		//mDirection * (mSpeed + mAcceleration)

		Transform* transform = GetGameObject()->GetComponent<Transform>();
		assert(transform != nullptr);

		transform->AddTranslate(mVelocity * deltaTime);
	}
}