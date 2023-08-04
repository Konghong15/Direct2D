#include "Rigidbody.h"
#include "GameObject.h"
#include "Transform.h"

namespace d2dFramework
{
	float Rigidbody::mGravityWeight = 9.8f;

	Rigidbody::Rigidbody(unsigned int id, GameObject* owner)
		: Component(id, owner)
		, mVelocity(0.f, 0.f)
		, mAcceleartion(0.f, 0.f)
		, mReflection(0.f, 0.f)
		, mMass(1.f)
		, mInvMass(1 / mMass)
		, mCOR(0.2f)
		, mGravityScale(1.f)
	{
	}

	void Rigidbody::Init()
	{
		IFixedUpdateable::Init();
	}

	void Rigidbody::FixedUpdate(float deltaTime)
	{
		Transform* transform = GetGameObject()->GetComponent<Transform>();

		AddVelocity({ 0, -mGravityWeight * mGravityScale });
		transform->AddTranslate(mVelocity * deltaTime);
	}

	void Rigidbody::Release()
	{
		IFixedUpdateable::Release();
	}
}