#include "AABBCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "Manifold.h"
#include "Rigidbody.h"
#include "Collision.h"
#include "OBBCollider.h"
#include "CircleCollider.h"

namespace d2dFramework
{
	AABBCollider::AABBCollider(unsigned int id, GameObject* owner)
		: Component(id, owner)
		, mbIsTrigger(false)
		, mOffset(0.f, 0.f)
		, mSize(1.f, 1.f)
		, mWorldAABB{ Vector2(-0.5f, -0.5f), Vector2(0.5f, 0.5f) }
	{
	}

	void AABBCollider::Init()
	{
		ICollideable::Init();
	}

	void AABBCollider::UpdateCollider()
	{
		Transform* transform = GetGameObject()->GetComponent<Transform>();

		const Vector2& SCALE = transform->GetScale();
		const Vector2& TRANSLATE = transform->GetTranslate();

		Vector2 size{ mSize.GetX() * SCALE.GetX(), mSize.GetY() * SCALE.GetY() };

		mWorldAABB.TopLeft = (size * -0.5f) + mOffset + TRANSLATE;
		mWorldAABB.BottomRight = (size * 0.5f) + mOffset + TRANSLATE;
	}

	bool AABBCollider::CheckCollision(ICollideable* other, Manifold* outManifold)
	{
		switch (other->GetColliderType())
		{
		case eColliderType::AABB:
		{
			AABBCollider* concreteOther = static_cast<AABBCollider*>(other);
			return Collision::CheckAABBToAABB(GetWorldAABB(), concreteOther->GetWorldAABB(), outManifold);
		}
		break;
		case eColliderType::OBB:
		{
			OBBCollider* concreteOther = static_cast<OBBCollider*>(other);
			return Collision::CheckAABBToOBB(GetWorldAABB(), concreteOther->GetWorldOBB(), outManifold);
		}
		break;
		case eColliderType::Circle:
		{
			CircleCollider* concreteOther = static_cast<CircleCollider*>(other);
			return Collision::CheckAABBToCircle(GetWorldAABB(), concreteOther->GetWorldCircle(), outManifold);
		}
		break;
		default:
			assert(false);
			return false;
			break;
		}
	}


	void AABBCollider::OnCollision(ICollideable* other, const Manifold& manifold)
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

	void AABBCollider::Release()
	{
		ICollideable::Release();
	}
}