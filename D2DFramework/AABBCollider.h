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

		virtual void UpdateCollider() override;
		virtual void HandleCollision(ICollideable* other) override;

		inline void SetIsTrigger(bool bisTrigger);
		inline void SetOffSet(const Vector2& offset);
		inline void SetSize(const Vector2& size);

		inline GameObject* GetGameObject() const override;
		inline eColliderType GetColliderType() const override;
		inline bool GetIsTrigger() const;
		inline const Vector2& GetOffset() const;
		inline const Vector2& GetSize() const;
		inline const AABB& GetWorldAABB() const;

	protected:
		virtual bool checkCollision(ICollideable* other, Manifold* outManifold) override;
		virtual void onCollision(ICollideable* other, const Manifold& manifold) override;

	private:
		bool mbIsTrigger;

		Vector2 mOffset;
		Vector2 mSize;

		AABB mWorldAABB;
	};

	void AABBCollider::SetIsTrigger(bool bisTrigger)
	{
		mbIsTrigger = bisTrigger;
	}
	void AABBCollider::SetOffSet(const Vector2& offset)
	{
		mOffset = offset;
	}
	void AABBCollider::SetSize(const Vector2& size)
	{
		mSize = size;
	}

	GameObject* AABBCollider::GetGameObject() const
	{
		return Component::GetGameObject();
	}
	eColliderType AABBCollider::GetColliderType() const
	{
		return eColliderType::AABB;
	}
	bool AABBCollider::GetIsTrigger() const
	{
		return mbIsTrigger;
	}
	const Vector2& AABBCollider::GetOffset() const
	{
		return mOffset;
	}
	const Vector2& AABBCollider::GetSize() const
	{
		return mSize;
	}
	const AABB& AABBCollider::GetWorldAABB() const
	{
		return mWorldAABB;
	}
}