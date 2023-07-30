#pragma once

#include "Component.h"
#include "ICollideable.h"
#include "OBB.h"
#include "AABB.h"

namespace d2dFramework
{
	class GameObject;

	class OBBCollider final : public Component, public ICollideable
	{
	public:
		OBBCollider(GameObject* owner);
		virtual ~OBBCollider() = default;

		virtual void UpdateCollider();
		virtual void HandleCollision(ICollideable* other);

		inline void SetIsTrigger(bool bisTrigger);

		inline bool GetIsTrigger() const;
		inline const OBB& GetWorldOBB() const;

	protected:
		virtual bool checkCollision(ICollideable* other, Manifold* outManifold) override;
		virtual void onCollision(ICollideable* other, const Manifold& manifold) override;

		using Component::GetGameObject;

	private:
		bool mbIsTrigger;

		Vector2 mOffset;
		AABB mLocalAABB;

		OBB mWorldOBB;
	};

	void OBBCollider::SetIsTrigger(bool bisTrigger)
	{
		mbIsTrigger = bisTrigger;
	}

	bool OBBCollider::GetIsTrigger() const
	{
		return mbIsTrigger;
	}
	const OBB& OBBCollider::GetWorldOBB() const
	{
		return mWorldOBB;
	}
}