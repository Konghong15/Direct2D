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
		, mColliderInfo{ eColliderType::AABB, {1, 1}, {0,0}, { 1.f, 1.f}, 0.f, {0.f, 0.f} }
		, mbIsTrigger(false)
	{
	}

	void BoxCollider::UpdateColliderInfo()
	{
		Transform* transform = GetGameObject()->GetComponent<Transform>();
		assert(transform != nullptr);

		mColliderInfo.Scale = transform->GetScale();
		mColliderInfo.RotateInDegree = transform->GetRotate();
		mColliderInfo.Translate = transform->GetTranslate();
		mColliderInfo.ColliderType = transform->GetRotate() == 0.f ? eColliderType::AABB : eColliderType::OBB;
		mColliderInfo.bIsCollision = false;
	}

	void BoxCollider::CheckCollision(ICollideable* other)
	{
		const ColliderInfo& otherColliderInfo = other->GetColliderInfo();
		bool bIsCollision;

		switch (mColliderInfo.ColliderType)
		{
		case eColliderType::AABB:
			switch (otherColliderInfo.ColliderType)
			{
			case eColliderType::AABB:
				bIsCollision = Collision::CheckAABBToAABB(Collision::MakeAABB(mColliderInfo), Collision::MakeAABB(otherColliderInfo));
				break;
			case eColliderType::OBB:
				bIsCollision = Collision::CheckAABBToOBB(Collision::MakeAABB(mColliderInfo), Collision::MakeOBB(otherColliderInfo));
				break;
			case eColliderType::Circle:
				bIsCollision = Collision::CheckAABBToCircle(Collision::MakeAABB(mColliderInfo), Collision::MakeCircle(otherColliderInfo));
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
				bIsCollision = Collision::CheckAABBToOBB(Collision::MakeAABB(otherColliderInfo), Collision::MakeOBB(mColliderInfo));
				break;
			case eColliderType::OBB:
				bIsCollision = Collision::CheckOBBToOBB(Collision::MakeOBB(mColliderInfo), Collision::MakeOBB(otherColliderInfo));
				break;
			case eColliderType::Circle:
				bIsCollision = Collision::CheckOBBToCircle(Collision::MakeOBB(mColliderInfo), Collision::MakeCircle(otherColliderInfo));
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

		if (bIsCollision)
		{
			OnCollision();
			other->OnCollision();
		}
	}

	void BoxCollider::OnCollision()
	{
		mColliderInfo.bIsCollision = true;
	}
}