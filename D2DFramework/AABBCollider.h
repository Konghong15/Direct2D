#pragma once

#include "Component.h"
#include "ICollideable.h"
#include "AABB.h"

namespace d2dFramework
{
	class GameObject;

	class AABBCollider final : public Component, public ICollideable
	{
	public:
		AABBCollider(GameObject* owner);
		virtual ~AABBCollider() = default;

		virtual void UpdateCollider();
		virtual void HandleCollision(ICollideable* other);

		inline void SetIsTrigger(bool bisTrigger);

		inline bool GetIsTrigger() const;
		inline const AABB& GetWorldAABB() const;

	protected:
		virtual bool checkCollision(ICollideable* other, Manifold* outManifold) override;
		virtual void onCollision(ICollideable* other, const Manifold& manifold) override;

		using Component::GetGameObject;

	private:
		bool mbIsTrigger;

		Vector2 mOffset;
		AABB mLocalAABB;

		AABB mWorldAABB;
	};

	void AABBCollider::SetIsTrigger(bool bisTrigger)
	{
		mbIsTrigger = bisTrigger;
	}

	bool AABBCollider::GetIsTrigger() const
	{
		return mbIsTrigger;
	}
	const AABB& AABBCollider::GetWorldAABB() const
	{
		return mWorldAABB;
	}
}