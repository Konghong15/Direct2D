#include <cassert>

#include "AABB.h"
#include "CircleCollider.h"
#include "Collision.h"
#include "Circle.h"
#include "OBB.h"
#include "GameObject.h"
#include "Transform.h"

namespace d2dFramework
{
	CircleCollider::CircleCollider(GameObject* owner)
		: Component(owner)
		, mColliderInfo{ eColliderType::Circle, {1, 1}, {0,0}, { 1.f, 1.f}, 0.f, {0.f, 0.f} }
		, mbIsTrigger(false)
	{
	}

	void CircleCollider::UpdateColliderInfo()
	{
		Transform* transform = GetGameObject()->GetComponent<Transform>();
		assert(transform != nullptr);

		mColliderInfo.Scale = transform->GetScale();
		mColliderInfo.RotateInDegree = transform->GetRotate(); // 이거 꼭 필요한가?
		mColliderInfo.Translate = transform->GetTranslate();

		mColliderInfo.bIsCollision = false;
		assert(mColliderInfo.ColliderType == eColliderType::Circle);
	}

	void CircleCollider::CheckCollision(ICollideable* other)
	{
		const ColliderInfo& otherColliderInfo = other->GetColliderInfo();
		bool bIsCollision = false;

		switch (otherColliderInfo.ColliderType)
		{
		case eColliderType::AABB:
			bIsCollision = Collision::CheckAABBToCircle(Collision::MakeAABB(otherColliderInfo), Collision::MakeCircle(mColliderInfo));
			break;
		case eColliderType::OBB:
			bIsCollision = Collision::CheckOBBToCircle(Collision::MakeOBB(otherColliderInfo), Collision::MakeCircle(mColliderInfo));
			break;
		case eColliderType::Circle:
			bIsCollision = Collision::CheckCircleToCircle(Collision::MakeCircle(mColliderInfo), Collision::MakeCircle(otherColliderInfo));
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

	void CircleCollider::OnCollision()
	{
		mColliderInfo.bIsCollision = true;
	}
}