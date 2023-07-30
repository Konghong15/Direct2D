#include "OBBCollider.h"
#include "GameObject.h"

namespace d2dFramework
{
	OBBCollider::OBBCollider(GameObject* owner)
		: Component(owner)
	{
	}

	void OBBCollider::UpdateCollider()
	{

	}

	void OBBCollider::HandleCollision(ICollideable* other)
	{

	}

	bool OBBCollider::checkCollision(ICollideable* other, Manifold* outManifold)
	{
		return true;
	}

	void OBBCollider::onCollision(ICollideable* other, const Manifold& manifold)
	{

	}
}