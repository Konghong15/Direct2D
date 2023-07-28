#pragma once

#include "Component.h"
#include "ICollideable.h"

#include "ColliderInfo.h"

namespace d2dFramework
{
	class GameObject;

	class BoxCollider final : public Component, public ICollideable
	{
	public:
		BoxCollider(GameObject* owner);
		virtual ~BoxCollider() = default;

		virtual void UpdateColliderInfo()  override;
		virtual void CheckCollision(ICollideable* other)  override;
		virtual void OnCollision() override;

		inline void SetColliderInfo(const ColliderInfo& colliderInfo);
		inline void SetIsTrigger(bool bisTrigger);

		inline const ColliderInfo& GetColliderInfo() const override;
		inline bool GetIsTrigger() const;

	private:
		bool mbIsTrigger;
		ColliderInfo mColliderInfo;
	};

	void BoxCollider::SetColliderInfo(const ColliderInfo& colliderInfo)
	{
		mColliderInfo = colliderInfo;
	}

	void BoxCollider::SetIsTrigger(bool bisTrigger)
	{
		mbIsTrigger = bisTrigger;
	}

	const ColliderInfo& BoxCollider::GetColliderInfo() const
	{
		return mColliderInfo;
	}

	bool BoxCollider::GetIsTrigger() const
	{
		return mbIsTrigger;
	}
}