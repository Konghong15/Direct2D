#include "Rigidbody.h"
#include "GameObject.h"
#include "Transform.h"

namespace d2dFramework
{
	Rigidbody::Rigidbody(GameObject* owner)
		: Component(owner)
		, mVelocity(0.f, 0.f)
		, mAcceleartion(0.f, 0.f)
		, mReflection(0.f, 0.f)
		, mMass(1.f)
		, mInvMass(1 / mMass)
		, mCOR(0.2f)
	{
	}

	void Rigidbody::FixedUpdate(float deltaTime)
	{
		Transform* transform = GetGameObject()->GetComponent<Transform>();

		transform->AddTranslate(mVelocity * deltaTime);
	}
}