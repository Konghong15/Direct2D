#pragma once

#include "Component.h"
#include "IUpdateable.h"

namespace d2dFramework
{
	class GameObject;
}

namespace d2dDemo
{
	class PlayerComponent
		: public d2dFramework::Component
		, public d2dFramework::IUpdateable
	{
	public:
		PlayerComponent(d2dFramework::GameObject* owner);
		virtual ~PlayerComponent() = default;

		virtual void Update(float deltaTime);
	};
}