#include "OBBCollider.h"
#include "GameObject.h"

namespace d2dFramework
{
	OBBCollider::OBBCollider(unsigned int id, GameObject* owner)
		: Component(id, owner)
	{
	}

	void OBBCollider::Init()
	{
		ICollideable::Init();
	}

	void OBBCollider::UpdateCollider()
	{

	}

	bool OBBCollider::CheckCollision(ICollideable* other, Manifold* outManifold)
	{
		return true;
	}

	void OBBCollider::OnCollision(ICollideable* other, const Manifold& manifold)
	{

	}

	void OBBCollider::Release()
	{
		ICollideable::Release();
	}
}