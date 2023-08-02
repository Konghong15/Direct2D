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
		OBBCollider(unsigned int id, GameObject* owner);
		virtual ~OBBCollider() = default;

		void Init() override;
		void UpdateCollider() override;
		bool CheckCollision(ICollideable* other, Manifold* outManifold) override;
		void OnCollision(ICollideable* other, const Manifold& manifold) override;
		void Release() override;

		inline void SetIsTrigger(bool bisTrigger);

		inline GameObject* GetGameObject() const override;
		inline eColliderType GetColliderType() const override;
		inline bool GetIsTrigger() const;
		inline const OBB& GetWorldOBB() const;

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

	GameObject* OBBCollider::GetGameObject() const
	{
		return Component::GetGameObject();
	}
	eColliderType OBBCollider::GetColliderType() const
	{
		return eColliderType::OBB;
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