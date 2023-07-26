#include "BoxCollider.h"

namespace d2dFramework
{
	BoxCollider::BoxCollider(GameObject* owner)
		: Component(owner)
		, mIs
	{
	}

	void BoxCollider::CheckCollision(ICollideable* other);
}