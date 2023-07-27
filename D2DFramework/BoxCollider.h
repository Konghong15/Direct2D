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

		virtual void UpdateColliderInfo();
		virtual void CheckCollision(ICollideable* other);

		inline void SetColliderInfo(const ColliderInfo& colliderInfo);

		inline const ColliderInfo& GetColliderInfo() override;
		inline bool GetIsCollision() const;


	private:
		bool mbIsCollision;
		ColliderInfo mColliderInfo;
	};

	void BoxCollider::SetColliderInfo(const ColliderInfo& colliderInfo)
	{
		mColliderInfo = colliderInfo;
	}

	const ColliderInfo& BoxCollider::GetColliderInfo()
	{
		return mColliderInfo;
	}

	bool BoxCollider::GetIsCollision() const
	{
		return mbIsCollision;
	}
}