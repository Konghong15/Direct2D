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
		CircleCollider(unsigned int id, GameObject* owner);
		~CircleCollider() override = default;

		void Init() override;
		void UpdateCollider() override;
		bool CheckCollision(ICollideable* other, Manifold* outManifold) override;
		void OnCollision(ICollideable* other, const Manifold& manifold) override;
		void Release() override;

		inline void SetIsTrigger(bool bisTrigger);
		inline void SetRadius(float radius);
		inline void SetOffset(const Vector2& offset);

		inline GameObject* GetGameObject() const override;
		inline eColliderType GetColliderType() const override;
		inline bool GetIsTrigger() const;
		inline float GetRadius() const;
		inline const Vector2& GetOffset() const;
		inline const Circle& GetWorldCircle() const;

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

	GameObject* CircleCollider::GetGameObject() const
	{
		return Component::GetGameObject();
	}
	eColliderType CircleCollider::GetColliderType() const
	{
		return eColliderType::Circle;
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