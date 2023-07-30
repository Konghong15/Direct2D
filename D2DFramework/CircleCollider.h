#pragma once

#include "Component.h"
#include "ICollideable.h"
#include "Circle.h"

namespace d2dFramework
{
	class GameObject;

	class CircleCollider final : public Component, public ICollideable
	{
	public:
		CircleCollider(GameObject* owner);
		virtual ~CircleCollider() = default;

		virtual void UpdateCollider() override;
		virtual void HandleCollision(ICollideable* other) override;

		inline void SetIsTrigger(bool bisTrigger);
		inline void SetRadius(float radius);
		inline void SetOffset(const Vector2& offset);

		inline eColliderType GetColliderType() const override;
		inline GameObject* GetGameObject() const override;
		inline bool GetIsTrigger() const;
		inline float GetRadius() const;
		inline const Vector2& GetOffset() const;
		inline const Circle& GetWorldCircle() const;

	protected:
		virtual bool checkCollision(ICollideable* other, Manifold* outManifold) override;
		virtual void onCollision(ICollideable* other, const Manifold& manifold) override;

	private:
		bool mbIsTrigger;

		Vector2 mOffset;
		float mLocalRadius;

		Circle mWorldCircle;
	};

	void CircleCollider::SetIsTrigger(bool bisTrigger)
	{
		mbIsTrigger = bisTrigger;
	}
	void CircleCollider::SetRadius(float radius)
	{
		mLocalRadius = radius;
	}
	void CircleCollider::SetOffset(const Vector2& offset)
	{
		mOffset = offset;
	}

	eColliderType CircleCollider::GetColliderType() const
	{
		return eColliderType::Circle;
	}
	GameObject* CircleCollider::GetGameObject() const
	{
		return Component::GetGameObject();
	}
	bool CircleCollider::GetIsTrigger() const
	{
		return mbIsTrigger;
	}
	float CircleCollider::GetRadius() const
	{
		return mLocalRadius;
	}
	const Vector2& CircleCollider::GetOffset() const
	{
		return mOffset;
	}
	const Circle& CircleCollider::GetWorldCircle() const
	{
		return mWorldCircle;
	}
}