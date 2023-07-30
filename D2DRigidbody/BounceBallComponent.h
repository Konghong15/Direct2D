#pragma once

#include <cassert>

#include "Component.h"
#include "IUpdateable.h"
#include "Vector2.h"

namespace d2dRigidbody
{
	class BounceBallComponent
		: public d2dFramework::Component
		, public d2dFramework::IUpdateable
	{
	public:
		BounceBallComponent(d2dFramework::GameObject* owner);
		virtual ~BounceBallComponent() = default;

		virtual void Update(float deltaTime) override;

		inline void SetSpped(const d2dFramework::Vector2& speed);

		inline const d2dFramework::Vector2& GetSpped(void) const;

	private:
		d2dFramework::Vector2 mSpeed;
	};

	void BounceBallComponent::SetSpped(const d2dFramework::Vector2& speed)
	{
		assert(speed.GetX() >= 0.f && speed.GetY() >= 0.f);

		mSpeed = speed;
	}

	const d2dFramework::Vector2& BounceBallComponent::GetSpped(void) const
	{
		return mSpeed;
	}
}