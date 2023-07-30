#include <cassert>
#include <cmath>

#include "AABB.h"
#include "CircleCollider.h"
#include "AABBCollider.h"
#include "Collision.h"
#include "Circle.h"
#include "OBB.h"
#include "OBBCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "Manifold.h"

namespace d2dFramework
{
	CircleCollider::CircleCollider(GameObject* owner)
		: Component(owner)
		, mbIsTrigger(false)
	{
	}

	void CircleCollider::UpdateCollider()
	{
		Transform* transform = GetGameObject()->GetComponent<Transform>();

		const Vector2& SCALE = transform->GetScale();
		mWorldCircle.Center.SetX(mOffset.GetX() * SCALE.GetX());
		mWorldCircle.Center.SetY(mOffset.GetY() * SCALE.GetY());
		mWorldCircle.Center += transform->GetTranslate();

		mWorldCircle.Radius = mLocalRadius * (SCALE.GetX() > SCALE.GetY() ? SCALE.GetX() : SCALE.GetY());
	}

	void CircleCollider::HandleCollision(ICollideable* other)
	{
		Manifold manifold;

		if (checkCollision(other, &manifold))
		{
			onCollision(other, manifold);
		}
	}

	bool CircleCollider::checkCollision(ICollideable* other, Manifold* outManifold)
	{
		switch (other->GetColliderType())
		{
		case eColliderType::AABB:
		{
			AABBCollider* concreteOther = static_cast<AABBCollider*>(other);
			return Collision::CheckAABBToCircle(concreteOther->GetWorldAABB(), GetWorldCircle(), outManifold);
		}
		break;
		case eColliderType::OBB:
		{
			OBBCollider* concreteOther = static_cast<OBBCollider*>(other);
			return Collision::CheckOBBToCircle(concreteOther->GetWorldOBB(), GetWorldCircle(), outManifold);
		}
		break;
		case eColliderType::Circle:
		{
			CircleCollider* concreteOther = static_cast<CircleCollider*>(other);
			return Collision::CheckCircleToCircle(GetWorldCircle(), concreteOther->GetWorldCircle(), outManifold);
		}
		break;
		default:
			assert(false);
			break;
		}
	}

	void CircleCollider::onCollision(ICollideable* other, const Manifold& manifold)
	{
		Rigidbody* rigidBody = GetGameObject()->GetComponent<Rigidbody>();
		Rigidbody* otherRigidBody = other->GetGameObject()->GetComponent<Rigidbody>();

		if (rigidBody == nullptr || otherRigidBody == nullptr)
		{
			return;
		}

		Vector2 rv = otherRigidBody->GetVelocity() - rigidBody->GetVelocity();
		float scalar = Vector2::Dot(rv, manifold.CollisionNormal);

		if (scalar > 0)
		{
			return;
		}

		float COR = min(rigidBody->GetCOR(), otherRigidBody->GetCOR());

		float j = -(1 + COR) * scalar;
		j /= rigidBody->GetInvMass() + otherRigidBody->GetInvMass();

		float massSum = rigidBody->GetMass() + otherRigidBody->GetMass();

		if (massSum == 0.f)
		{
			return;
		}

		Vector2 impulse = manifold.CollisionNormal * j;
		rigidBody->AddVelocity(impulse * -rigidBody->GetInvMass());
		otherRigidBody->AddVelocity(impulse * otherRigidBody->GetInvMass());

		const float percent = 0.2f;
		const float slop = 0.01f;
		Vector2 correction = manifold.CollisionNormal * (std::max<float>(manifold.Penetration - slop, 0.f) / (rigidBody->GetInvMass() + otherRigidBody->GetInvMass()) * percent);

		rigidBody->AddVelocity(correction * -rigidBody->GetInvMass());
		otherRigidBody->AddVelocity(correction * otherRigidBody->GetInvMass());
	}

	//void CircleCollider::CheckCollision(ICollideable* other)
	//{
	//	const ColliderInfo& otherColliderInfo = other->GetColliderInfo();
	//	bool bIsCollision = false;

	//	switch (otherColliderInfo.ColliderType)
	//	{
	//	case eColliderType::AABB:
	//		bIsCollision = Collision::CheckAABBToCircle(Collision::MakeAABB(otherColliderInfo), Collision::MakeCircle(mColliderInfo));
	//		break;
	//	case eColliderType::OBB:
	//		bIsCollision = Collision::CheckOBBToCircle(Collision::MakeOBB(otherColliderInfo), Collision::MakeCircle(mColliderInfo));
	//		break;
	//	case eColliderType::Circle:
	//		bIsCollision = Collision::CheckCircleToCircle(Collision::MakeCircle(mColliderInfo), Collision::MakeCircle(otherColliderInfo));
	//		break;
	//	default:
	//		assert(false);
	//		break;
	//	}

	//	if (bIsCollision)
	//	{
	//		OnCollision(other);
	//		other->OnCollision(this);
	//	}
	//}

	//// 충돌 처리 이후 리지드 바디가 있을때 처리
	//void CircleCollider::OnCollision(ICollideable* other)
	//{
	//	// if isTrigger return;

	//	mColliderInfo.bIsCollision = true;

	//	Rigidbody* rigidbody = GetGameObject()->GetComponent<Rigidbody>();
	//	if (rigidbody != nullptr)
	//	{
	//		const ColliderInfo& info = GetColliderInfo();
	//		const ColliderInfo& otherInfo = other->GetColliderInfo();

	//		if (otherInfo.ColliderType == eColliderType::Circle)
	//		{
	//			Vector2 reflect = (info.Offset + info.Translate) - (otherInfo.Offset + otherInfo.Translate);
	//			rigidbody->AddVelocity(reflect);
	//		}
	//		else if (otherInfo.ColliderType == eColliderType::AABB)
	//		{
	//			rigidbody->SetVelocity(rigidbody->GetVelocity() * -1);
	//		}
	//	}
	//}
}