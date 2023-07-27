#include <cassert>

#include "AABB.h"
#include "BoxCollider.h"
#include "Collision.h"
#include "Circle.h"
#include "OBB.h"
#include "GameObject.h"
#include "Transform.h"

namespace d2dFramework
{
	BoxCollider::BoxCollider(GameObject* owner)
		: Component(owner)
		, mbIsCollision(false)
		, mColliderInfo{ eColliderType::AABB, {1, 1}, {0,0}, { 1.f, 1.f}, 0.f, {0.f, 0.f} }
	{
	}

	void BoxCollider::UpdateColliderInfo()
	{
		Transform* transform = GetGameObject()->GetComponent<Transform>();
		assert(transform != nullptr);

		mColliderInfo.Scale = transform->GetScale();
		mColliderInfo.RotateInRadian = transform->GetRotate();
		mColliderInfo.Translate = transform->GetTranslate();
		mColliderInfo.ColliderType = transform->GetRotate() == 0.f ? eColliderType::AABB : eColliderType::OBB;
	}

	void BoxCollider::CheckCollision(ICollideable* other)
	{
		const ColliderInfo& otherColliderInfo = other->GetColliderInfo();

		switch (mColliderInfo.ColliderType)
		{
		case eColliderType::AABB:
			switch (otherColliderInfo.ColliderType)
			{
			case eColliderType::AABB:
				mbIsCollision = Collision::CheckAABBToAABB(Collision::MakeAABB(mColliderInfo), Collision::MakeAABB(otherColliderInfo));
				break;
			case eColliderType::OBB:
				mbIsCollision = Collision::CheckAABBToOBB(Collision::MakeAABB(mColliderInfo), Collision::MakeOBB(otherColliderInfo));
				break;
			case eColliderType::Circle:
				mbIsCollision = Collision::CheckAABBToCircle(Collision::MakeAABB(mColliderInfo), Collision::MakeCircle(otherColliderInfo));
				break;
			default:
				assert(false);
				break;
			}
			break;
		case eColliderType::OBB:
			switch (otherColliderInfo.ColliderType)
			{
			case eColliderType::AABB:
				mbIsCollision = Collision::CheckAABBToOBB(Collision::MakeAABB(otherColliderInfo), Collision::MakeOBB(mColliderInfo));
				break;
			case eColliderType::OBB:
				mbIsCollision = Collision::CheckOBBToOBB(Collision::MakeOBB(mColliderInfo), Collision::MakeOBB(otherColliderInfo));
				break;
			case eColliderType::Circle:
				mbIsCollision = Collision::CheckOBBToCircle(Collision::MakeOBB(mColliderInfo), Collision::MakeCircle(otherColliderInfo));
				break;
			default:
				assert(false);
				break;
			}
			break;
		case eColliderType::Circle:
			assert(false);
			break;
		default:
			assert(false);
			break;
		}
	}
}