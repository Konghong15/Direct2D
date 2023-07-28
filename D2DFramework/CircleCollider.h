#pragma once

#include "Component.h"
#include "ICollideable.h"

#include "ColliderInfo.h"

namespace d2dFramework
{
	class GameObject;

	class CircleCollider final : public Component, public ICollideable
	{
	public:
		CircleCollider(GameObject* owner);
		virtual ~CircleCollider() = default;

		virtual void UpdateColliderInfo() override;
		virtual void CheckCollision(ICollideable* other) override;
		virtual void OnCollision() override;

		inline void SetColliderInfo(const ColliderInfo& colliderInfo);
		inline void SetIsTrigger(bool bisTrigger);

		inline const ColliderInfo& GetColliderInfo() const override;
		inline bool GetIsTrigger() const;


	private:
		bool mbIsTrigger;
		ColliderInfo mColliderInfo;
	};

	void CircleCollider::SetColliderInfo(const ColliderInfo& colliderInfo)
	{
		mColliderInfo = colliderInfo;
	}

	void CircleCollider::SetIsTrigger(bool bisTrigger)
	{
		mbIsTrigger = bisTrigger;
	}

	const ColliderInfo& CircleCollider::GetColliderInfo() const
	{
		return mColliderInfo;
	}

	bool CircleCollider::GetIsTrigger() const
	{
		return mbIsTrigger;
	}
}