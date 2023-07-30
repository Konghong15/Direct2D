#include "AABBCollider.h"
#include "GameObject.h"

namespace d2dFramework
{
	AABBCollider::AABBCollider(GameObject* owner)
		: Component(owner)
	{
	}

	void AABBCollider::UpdateCollider()
	{

	}
	void AABBCollider::HandleCollision(ICollideable* other)
	{

	}

	bool AABBCollider::checkCollision(ICollideable* other, Manifold* outManifold)
	{
		return true;
	}
	void AABBCollider::onCollision(ICollideable* other, const Manifold& manifold)
	{

	}
}