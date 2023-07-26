#pragma once

#include "Vector2.h"
#include "Component.h"
#include "IUpdateable.h"

namespace d2dFramework
{
	class GameObject;

	class Movement : public Component, public IUpdateable
	{
	public:
		Movement(GameObject* onwer);
		virtual ~Movement() = default;

		virtual void Update(float deltaTime);

	private:
		Vector2 mVelocity;
		Vector2 mDirection;
		float mSpeed;
	};
}