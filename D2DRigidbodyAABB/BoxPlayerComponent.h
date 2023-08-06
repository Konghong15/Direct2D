#pragma once

#include <cassert>

#include "Component.h"
#include "IUpdateable.h"
#include "Vector2.h"

namespace d2dFramework
{
	class GameObject;
}

namespace d2dRigidbodyAABB
{

	class BoxPlayerComponent
		: public d2dFramework::Component
		, public d2dFramework::IUpdateable
	{
	public:
		BoxPlayerComponent(unsigned int id, d2dFramework::GameObject* owner);
		virtual ~BoxPlayerComponent() = default;

		virtual void Init() override;
		virtual void Update(float deltaTime) override;
		virtual void Release() override;

		inline void SetSpped(const d2dFramework::Vector2& speed);

		inline d2dFramework::GameObject* GetGameObject() const override;
		inline unsigned int GetId() const override;
		inline const d2dFramework::Vector2& GetSpped(void) const;

	private:
		d2dFramework::Vector2 mSpeed;
	};

	void BoxPlayerComponent::SetSpped(const d2dFramework::Vector2& speed)
	{
		assert(speed.GetX() >= 0.f && speed.GetY() >= 0.f);

		mSpeed = speed;
	}

	d2dFramework::GameObject* BoxPlayerComponent::GetGameObject() const
	{
		return Component::GetGameObject();
	}
	unsigned int BoxPlayerComponent::GetId() const
	{
		return BaseEntity::GetId();
	}
	const d2dFramework::Vector2& BoxPlayerComponent::GetSpped(void) const
	{
		return mSpeed;
	}
}