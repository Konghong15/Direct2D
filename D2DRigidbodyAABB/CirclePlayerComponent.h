#pragma once

#include <cassert>

#include "Component.h"
#include "IUpdateable.h"
#include "Vector2.h"

namespace d2dRigidbodyAABB
{
	class CirclePlayerComponent
		: public d2dFramework::Component
		, public d2dFramework::IUpdateable
	{
	public:
		CirclePlayerComponent(unsigned int id, d2dFramework::GameObject* owner);
		virtual ~CirclePlayerComponent() = default;

		virtual void Init() override;
		virtual void Update(float deltaTime) override;
		virtual void Release() override;

		inline void SetSpped(const d2dFramework::Vector2& speed);

		inline const d2dFramework::Vector2& GetSpped(void) const;

	private:
		d2dFramework::Vector2 mSpeed;
	};

	void CirclePlayerComponent::SetSpped(const d2dFramework::Vector2& speed)
	{
		assert(speed.GetX() >= 0.f && speed.GetY() >= 0.f);

		mSpeed = speed;
	}

	const d2dFramework::Vector2& CirclePlayerComponent::GetSpped(void) const
	{
		return mSpeed;
	}
}